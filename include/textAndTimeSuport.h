
#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif

#include <ctime>
#include <iostream>
#include <string>
#include <cmath>

#include <cstdlib>  //for rand & srand, system

using uint = unsigned int;
using std::string;
using std::cout;
using std::endl;

namespace mt_text_time {

    #ifdef _WIN32
	void set_window_state(bool state);
	void set_text_color(int color);
	void set_cursor_visibility(bool visible);
	void resize_window(int width, int height);
	void clearConsole();
	#elif __linux__ 
	void clearConsole();
    #endif

	bool findInCharArray(const char * word, uint wordLength, const char * specificWord, uint specificWordLength);
	bool isInString(const std::string& text, const std::string& word);
	char numberToChar(const int& number);
	string integerToString(const int& number);
	tm* get_time();
	double getRandomNumber();
}