#define STB_IMAGE_IMPLEMENTATION


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <cstring>

#include "vectorSuport.h"
#include "fileSuport.h"
#include "textAndTimeSuport.h"
#include "stb_image.h"

using uint = unsigned int;
using std::cout;
using std::endl;
using std::string;

namespace mt_draw {

    class shader {
        uint shaderProgram = 0;
        uint vertexShader = 0, fragmentShader = 0;
        string vertexShaderSource;
        string fragmentShaderSource;
    public:
        shader(string fileName) {
            loadShaderSources(fileName);
            const char *vertexPtr = vertexShaderSource.c_str();
            const char *fragmentPtr = fragmentShaderSource.c_str();

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexPtr, NULL);
            glCompileShader(vertexShader);

            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentPtr, NULL);
            glCompileShader(fragmentShader);
            
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            //it's easier to use it immediately...
            glUseProgram(shaderProgram);
        }
        ~shader() {
            glDeleteProgram(shaderProgram);
        }

        void loadShaderSources(string fileName) {
            string shaderSource = mt_file::readFileByLine(fileName);
            stringstream vertexSource, fragmentSource;
            uint lineCount = 0, pointer = 0;
            char line[80] = "";
            bool switchStatus = false;
            for (uint i = 0; i < shaderSource.size(); i++) {
                if (shaderSource[i] == '\n') {
                    if (mt_text_time::findInCharArray(line, 80, "#switch", 7)) { 
                        switchStatus = true;
                    }
                    else {
                        if (switchStatus) {
                            fragmentSource << line << endl;
                        }
                        else {
                            vertexSource << line << endl;
                        }
                    }
                    memset(line, 0, 80);
                    pointer = 0;
                }
                else {
                    line[pointer] = shaderSource[i];
                    pointer++;
                }
            }
            vertexShaderSource = vertexSource.str();
            fragmentShaderSource = fragmentSource.str();
        }
        void useShader() {
            glUseProgram(shaderProgram);
        }
        uint& getShaderProgram() { return shaderProgram; }
    
        //set uniforms...
        void setBool(const std::string &name, bool value) const
        {         
            glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
        }
        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
        }
        void setFloat(const std::string &name, float value) const
        { 
            glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
        } 
    };

    typedef struct verticesData {
        float* vertices = nullptr;
        uint* indices = nullptr;
        uint verticesCount = 0;
        uint indicesCount = 0;
    } verticesData;

    typedef struct vertexAttributeData {
        uint location;
        uint size;
        uint startingPosition;
    } vertexAttributeData;

    class object {
        float* vertices = nullptr;
        uint* indices = nullptr;
        uint verticesCount = 0;
        uint indicesCount = 0;
        uint vertexArrayObject = 0;
        uint vertexBufferObject = 0; 
        uint elementBufferObject = 0;
    public:
        object(const verticesData& data, vector<vertexAttributeData> vertexAttributes = vector<vertexAttributeData>(1, { 0, 3, 0 })) {  //default vector of attributes as a parameter
            this->vertices = data.vertices;
            this->indices = data.indices;
            this->verticesCount = data.verticesCount;
            this->indicesCount = data.indicesCount;
            
            generateBuffers(vertexAttributes);
        }
        ~object() {
            glDeleteVertexArrays(1, &vertexArrayObject);
            glDeleteBuffers(1, &vertexBufferObject);
            glDeleteBuffers(1, &elementBufferObject);
        }

        uint calculateStride(vector<vertexAttributeData> vertexAttributes) {
            uint stride = 0;
            for (vertexAttributeData& atribute : vertexAttributes) {
                stride += atribute.size;
            }
            return stride;
        }

        void generateBuffers(vector<vertexAttributeData> vertexAttributes) {
            glGenVertexArrays(1, &vertexArrayObject);
            glGenBuffers(1, &vertexBufferObject);
            glGenBuffers(1, &elementBufferObject);

            glBindVertexArray(vertexArrayObject);

            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
            glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(uint), indices, GL_STATIC_DRAW);

            uint stride = calculateStride(vertexAttributes);

            for (vertexAttributeData& atribute : vertexAttributes) {
                glVertexAttribPointer(atribute.location, atribute.size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(atribute.startingPosition * sizeof(float)));
                glEnableVertexAttribArray(atribute.location);
            }

            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glBindVertexArray(0); 
        }
        uint& getVertexArrayObject() { return vertexArrayObject; }
        uint& getIndicesCount() { return indicesCount; }
    };

    class texture {
        uint id = 0;
        uint unit = 0; //min 0, max 15  (max 16 texture units)
    public:
        texture(const string& path, bool transparency, const uint& unit = 0) {
            this->unit = unit;
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            int width, height, nrChanels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChanels, 0);
            if (data) {
                if (transparency) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
            }
            else {
                cout << "Failed to load texture" << endl;
            }
            stbi_image_free(data);
        }
        void setUnit(shader& shader) {
            //sampler2D textures in shader must allways be in this format => (texture(0-15))!!!!
            string texture = "texture" + mt_text_time::integerToString(unit);
            shader.setInt(texture, unit);
        }
        void activateUnit() {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, id);
        }
    };

    class openGlManager {
        GLFWwindow* window = nullptr;
        object* drawableObject = nullptr;
        shader* currentShader = nullptr;
    public:
        openGlManager(uint windowWidth, uint windowHeight, string windowName) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #ifdef __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
            if (window == NULL)
            {
                cout << "Failed to create GLFW window" << endl;
                glfwTerminate();
                exit(1);
            }
            glfwMakeContextCurrent(window);            

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                cout << "Failed to initialize GLAD" << endl;
                exit(1);
            }
        }
        ~openGlManager() {
            glfwTerminate();
        }

        void setShader(shader* currentShader) {
            this->currentShader = currentShader;
        }
        void setObject(object* drawableObject) {
            this->drawableObject = drawableObject;
        }
        GLFWwindow* getWindow() {
            return window;
        }
        void setFrameBufferSizeCallback(void (* frameBufferSizeCallback)(GLFWwindow* window, int width, int height)) {
            glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
        }

        void loop(void (* proceessInput)(GLFWwindow* window)) {
            glUseProgram(currentShader->getShaderProgram());
            glBindVertexArray(drawableObject->getVertexArrayObject()); 
            while(!glfwWindowShouldClose(this->window)) {
                proceessInput(this->window);


                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glDrawElements(GL_TRIANGLES, drawableObject->getIndicesCount(), GL_UNSIGNED_INT, 0);


                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }

    };

}