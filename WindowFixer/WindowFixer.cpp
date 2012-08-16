// File:		WindowFixer.cpp
// Author:		John "Purebe" Conder
// Date:		08/16/2012
// Purepose:	To easily resize a window-application to a pre-desired exact size.

#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

// Converts from c-style string to int
int ToInteger(char const arg[])
{
	std::stringstream strm(arg);
	int ret;
	strm >> ret;
	return ret;
}

// Finds the upper left corner of the centered position.
void FindCenter(int& x, int& y, int const width, int const height)
{
	HWND const hWin = GetDesktopWindow();
	RECT rc;
	GetWindowRect(hWin, &rc);

	x = rc.right / 2;
	y = rc.bottom / 2;

	x -= width/2;
	y -= height/2;
}

// Attempts to resize the given window with the given position and size.
bool ResizeWindow(std::string const& windowTitle, int const x1, int const y1, int const x2, int const y2)
{
	HWND const hWin = FindWindow(nullptr, windowTitle.c_str());

	BOOL const ret = MoveWindow(hWin, x1, y1, x2, y2, true);

	if ( ret )
		return true;
	return false;
}

int main(int argc, char* argv[])
{
	std::cout << "WindowFixer v0.0.1" << std::endl;

	std::string title;
	int width, height;
	int x, y;

	if ( argc == 4 )
	{
		// Batch mode: Expect command line arguments in this form:
		// WindowFixer.exe "Window Title" width height
		title = argv[1];
		width = ToInteger(argv[2]);
		height = ToInteger(argv[3]);
	}
	else
	{
		if ( argc > 1 )
		{
			std::cout << "Command line format is: WindowFixer.exe \"Window Title\" width height" << std::endl;
		}

		// Ask the user:
		std::cout << "Window Title: ";
		std::getline(std::cin, title);

		std::cout << "Window Width: ";
		std::cin >> width;

		std::cout << "Window Height: ";
		std::cin >> height;
	}

	FindCenter(x, y, width, height);

	if ( !ResizeWindow(title, x, y, width, height) )
	{
		std::cout << "Something went wrong.  Are you sure you typed the Window Title correctly?" << std::endl;
		std::cin.get();
		return 1;
	}

	return 0;
}