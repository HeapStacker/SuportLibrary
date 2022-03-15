#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

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
}