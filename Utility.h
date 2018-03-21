#pragma once

/*
	C++ Console App Utilities
	Khalid Ali 2018
	http://khalidali.co.uk/
*/

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <windows.h>
#include <conio.h>

using namespace std;

//Enumeration of the possible colours to be used when modifying console colour
enum Colour { BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, DEFAULT, GRAY, LIGHT_BLUE,
	LIGHT_GREEN, LIGHT_AQUA, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, WHITE };

class Utility
{
private:
	Utility() {}; //prevents class from being constructed
	~Utility() {};
public:	
	//Requests a yes/no (or similar varied) response from the user
	//Parametres:
		//(mssage) prompt message for request
	static bool getYesNo(string message)
	{
		string input = "";
		bool isYes = true;

		cout << message;
		cin >> input;
		cin.ignore();
		while (input != "Y" && input != "Yes" && input != "YES" && input != "yes" && input != "N" && input != "No" && input != "NO" && input != "no" && input != "y" && input != "n")
		{
			cout << "ERROR: you can only enter 'Yes', 'No' or a similar variation.\nTry again: ";
			cin >> input;
		}

		if (input == "Y" || input == "Yes" || input == "YES" || input == "yes" || input == "y")
			isYes = true;
		else if (input == "N" || input == "No" || input == "NO" || input == "no" || input == "n")
			isYes = false;
		return isYes;
	}

	//Requests an integer value from the user
	//Parametres:
		//(message) prompt message for request
		//(min) minimum bound accepted from input (defaulted as minimum int value)
		//(max) maximum bound accepted from input (defaulted as maximum int value)
	static int getInteger(string message, int min = -2147483647, int max = 2147483647)
	{
		string input = "";
		int processedInput = -2147483647;

		cout << message;
		cin >> input;
		cin.ignore();
		stringstream strStream(input);
		strStream >> processedInput;
		while (processedInput < min || processedInput > max)
		{
			cout << "ERROR: you can only enter a whole number between " << min << " and " << max << ".\nTry again: ";
			cin >> input;
			cin.ignore();
			stringstream strStream(input);
			strStream >> processedInput;
		}
		return processedInput;
	}

	//Clears the console output screen
	static void clearScreen(void) { system("cls"); }

	//Changes the console window's title
	//Parametres:
		//(nTitle) desired new console window title
	static void setWindowTitle(string nTitle) { SetConsoleTitle(nTitle.c_str()); }

	//Changes the console output's colour
	//Parametres:
		//(fore) desired enumerated foreground (text) colour
		//(back) desired enumerated background colour (defaulted as black)
	static void setColour(Colour fore, Colour back = BLACK)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		int colour = fore * 16 + back;
		SetConsoleTextAttribute(handle, back);
	}
};