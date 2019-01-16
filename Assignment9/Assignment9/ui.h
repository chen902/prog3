/**@file  ui.h
 * Author: Chen Kasirer
 *
 * Created on Januray 16, 2019
 */

#pragma once
#include <string>
#include <iostream>
#include <vector>


using namespace std;

class ui
{
public:
	void displayMenu(string title, string* options, size_t numOfOptions, bool withClear = false);
	string getString();
	void output(const string& str);
	
	void clear();
};

