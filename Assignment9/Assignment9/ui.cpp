#include "ui.h"

using namespace std;

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

string ui::getString() {
	string line;
	getline(cin, line);

	return line;
}
int ui::promptUser(string* options, size_t numOfOptions)
{
	this->clear();
	for (size_t i = 0; i < numOfOptions; ++i) {
		cout << to_string(i+1) << ". " << options[i] << "\n";
	}
	
	cout << "Please choose one of the above options" << endl;

	string choice;
	
	getline(cin, choice);

	return stoi(choice);
}

string ui::promptUser(string prompt)
{
	string input;
	getline(cin, input);
	return input;
}

void ui::output(const string & str)
{
	cout << str << endl;
}

void ui::clear() {
	system("CLS");
}
