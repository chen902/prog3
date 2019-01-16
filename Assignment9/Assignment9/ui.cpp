/**@file  ui.cpp
 * Author: Chen Kasirer
 *
 * Created on Januray 16, 2019
 *
 * This class manages all interaction with the console for the trainer program.
 */

#include "ui.h"

using namespace std;

/**
 * Displays a choice menu. If withClear is set to true, the console is cleared prior to printing the menu.
 */
void ui::displayMenu(string title, string* options, size_t numOfOptions, bool withClear)
{
	// clear console before printing menu
	if(withClear)
		this->clear();

	this->output(title);
	for (size_t i = 0; i < numOfOptions; ++i) {
		cout << to_string(i + 1) << ". " << options[i] << "\n";
	}

	cout << "Please choose one of the above options" << endl;
}

/**
 * Prompts the user and returns the line typed.
 */
string ui::getString() {
	string line;
	getline(cin, line);

	return line;
}

/**
 * Prints the received message to the console
 */
void ui::output(const string & str)
{
	cout << str << endl;
}

/**
 * Clears the console. (Win32 only)
 */
void ui::clear() {
	system("CLS");
}
