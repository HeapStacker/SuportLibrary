
#include "textAndTimeSuport.h"

namespace mt_text_time {

    #ifdef _WIN32
	void set_window_state(bool state) {
		if (state) ShowWindow(GetConsoleWindow(), SW_SHOW);
		else ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	void set_text_color(int color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
	void set_cursor_visibility(bool visible)
	{
		CONSOLE_CURSOR_INFO info;
		if (visible) info.bVisible = TRUE;
		else info.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	}
	void resize_window(int width, int height)
	{
		RECT consoleRect;
		HWND console = GetConsoleWindow();
		GetWindowRect(console, &consoleRect);
		MoveWindow(console, consoleRect.left, consoleRect.top, width, height, TRUE);
	}
	void clearConsole() {
		system("cls");
	}
	#elif __linux__ 
	void clearConsole() {
		system("clear");
	}
    #endif

	bool findInCharArray(const char * word, uint wordLength, const char * specificWord, uint specificWordLength) {
		bool contains = false;
		if (wordLength >= specificWordLength) {
			for (uint i = 0; i < wordLength; i++) {
				if (word[i] == specificWord[0]) {
					contains = true;
					for (uint j = 0; j < specificWordLength; j++) {
						if (word[i + j] != specificWord[j]) contains = false;
					}
				}
			}
		}
		return contains;
	}

	bool isInString(const std::string& text, const std::string& word) {
		size_t found = text.find(word);
    	if (found != std::string::npos)
        	return true;
		return false;
	}

	char numberToChar(const int& number) {
		if (number >= -9 && number <= 9) {
			switch (std::abs(number)) {
				case 0: return '0';
				case 1: return '1';
				case 2: return '2';
				case 3: return '3';
				case 4: return '4';
				case 5: return '5';
				case 6: return '6';
				case 7: return '7';
				case 8: return '8';
				case 9: return '9';
				default: return 'x';
			}
		}
		std::cout << "Number must be in range (-9, 9).\n";
		return 'x';
	}

	string integerToString(const int& number) {
		uint counter = 1, temp1 = std::abs(number), temp2 = std::abs(number), unit;
		string textNumber;
		if (number < 0) textNumber = "-";
		while (temp1 /= 10) {
			counter++;
		}
		char *array = new char[counter];
		for (uint i = 0; i < counter; i++) {
			unit = temp2 % 10;
			array[counter - 1 -i] = numberToChar(unit);
			temp2 /= 10;
		}
		textNumber += array;
		delete array;
		return textNumber;
	}

	//time suport
	tm* get_time() {
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		return localtime(&rawtime);
	}

	//generate random number
	double getRandomNumber() {
		static bool called = false;
		if (!called) {
			srand(time(0));
			called = true;
		}
		return rand();
	}
}