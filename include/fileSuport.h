#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using std::addressof;

namespace mt_file {
    //reading normal files...
    string readFileByLine(string path);
    string readFileByString(string path);
    string readFileByCharacter(string path);

    //appending to normal files...
    void appendToFile(string path, string word);
    void appendToFile(string path, char character);

    //delete a normal file...
    void deleteFileData(string path);

    //reading a binary file... 
    //not so good because you can see info in bin file
    void writeToBinaryFile(string path, string data);
    string readBinaryFile(string path);


    //use the following functions for reading/writing objects from/to bin file...
    //objects that you save in to bin file must have finate size, instead of pointers save whole char arrays
    template<typename T>
    void writeToBinaryFile(string path, T data) {
        ofstream fileWriter;
        fileWriter.open(path.c_str(), std::ios::binary);
        if (fileWriter) {
            fileWriter.write((char *)addressof(data), sizeof(data));
        }
        fileWriter.close();
    }
    template<typename T>
    T readBinaryFile(string path) {
        T data;
        ifstream fileReader;
        fileReader.open(path.c_str(), std::ios::binary);
        if (fileReader) {
            fileReader.read((char *)&data, sizeof(data));
        }
        fileReader.close();
        return data;
    }

}