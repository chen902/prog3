#pragma once
#include <string>
#include <iostream>
#include <vector>


using namespace std;

class ui
{
public:
	void displayMenu(string title, string* options, size_t numOfOptions, bool withClear = false);
	int promptUser(string* options, size_t numOfOptions);
	string promptUser(string prompt);
	string getString();
	void output(const string& str);
	
	void clear();
};

