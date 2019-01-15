#include "ui.h"

using namespace std;


ui::ui()
{
}


ui::~ui()
{
}

void ui::displayMenu()
{
	string menu = "Welcome to the world's ugliest vocabulary trainer!\n Please choose a language below:\n";
	menu += "1. German -> English\n";
	menu += "2. German -> English\n";
	menu += "3. German -> English\n";
	menu += "4. German -> English\n";
	cout << menu;
}

void ui::clear() {
	system("CLS");
}
