#include "trainer.h"

using namespace std;


trainer::trainer() : ui()
{
}


trainer::~trainer()
{
}

void trainer::start()
{
	ui->displayMenu();
	string input;
	
	while (input != "exit"){
		getline(cin, input);
		ui->clear();
		ui->displayMenu();
	}
}

void trainer::initialize()
{
	userChoice arr[] = {
		*(new userChoice("Practice!", this->practice)),
		*(new userChoice("Add Words", this->addWord)),
		*(new userChoice("Exit", this->exit))
	};

	vector<userChoice>* options = new vector<userChoice>();
	options->assign(arr, arr+sizeof(arr));

	screen s("Main Menu", options);
	this->screens["mainmenu"] = s;
}

void trainer::promptUser(string screen)
{
	string title = this->screens.at(screen).title;
	vector<userChoice>::iterator t = this->screens.at(screen).options->begin();
	
	int choise = 0;
	
	while (t  != this->screens.at(screen).options->end()) {
		cout << to_string(++choise) << ". " << t->name << "\n";
	}

	string choice;

	getline(cin, choice);

	t = this->screens.at(screen).options->begin + stoi(choice);
	(*t).f();
}
