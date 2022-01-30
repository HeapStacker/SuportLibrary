
#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif

#include <ctime>

namespace mt_cmd {

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
    #endif

	//time suport
	tm* get_time() {
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		return localtime(&rawtime);
	}
}