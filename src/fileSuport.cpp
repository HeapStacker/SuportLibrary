#include "fileSuport.h"

namespace mt_file
{
    string readFileByLine(string path)
    {
        ifstream fileReader(path);
        stringstream text;
        if (fileReader)
        {
            string line;
            while (getline(fileReader, line))
            {
                text << line << "\n";
            }
        }
        fileReader.close();
        return text.str();
    }

    string readFileByString(string path)
    {
        ifstream fileReader(path);
        stringstream text;
        if (fileReader)
        {
            string line;
            while (fileReader >> line)
            {
                text << line << "\n";
            }
        }
        fileReader.close();
        return text.str();
    }

    string readFileByCharacter(string path)
    {
        ifstream fileReader(path);
        stringstream text;
        if (fileReader)
        {
            char line;
            while (fileReader >> line)
            {
                text << line << "\n";
            }
        }
        fileReader.close();
        return text.str();
    }


    void appendToFile(string path, string word) {
        ofstream fileWriter(path, std::ios::app);
        if (fileWriter) {
            fileWriter << word;
        }
        fileWriter.close();
    }

    void appendToFile(string path, char character) {
        ofstream fileWriter(path, std::ios::app);
        if (fileWriter) {
            fileWriter << character;
        }
        fileWriter.close();
    }

    void deleteFileData(string path) {
        ofstream fileWriter(path);
        fileWriter.close();
    }


    void writeToBinaryFile(string path, string data) {
        ofstream fileWriter(path, std::ios::binary);
        if (fileWriter) {
            int length = data.size();
            for (int i = 0; i <= length; i++) {
                fileWriter.put(data[i]);
            }
        }
        fileWriter.close();
    }

    string readBinaryFile(string path) {
        ifstream fileReader(path, std::ios::binary);
        int length = 0;
        char *varchar = nullptr;
        vector<char> characters;
        if (fileReader) {
            char ch;
            while(fileReader.good()) {
                fileReader.get(ch);
                characters.push_back(ch);
            }
            length = characters.size();
            varchar = new char[length];
            for (size_t i = 0; i < length; i++)
            {
                varchar[i] = characters[i];
            }
        }
        fileReader.close();
        return varchar;
    }
}