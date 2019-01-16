#include "trainer.h"

using namespace std;


trainer::trainer() : ui()
{
	// Allocate memory for the priority queue
	this->words = new priority_queue<word, vector<word>, WordCompare>();
	this->answered_correctly = new vector<word>();
}


trainer::~trainer()
{
	delete this->ui;
	delete this->words;
	delete this->answered_correctly;
}

void trainer::start()
{
	string filename = "wordbank.csv";

	this->loadFromFile(filename);

	string t_mainmenu = "Welcome to Vocabu-hell!";
	string o_mainmenu[]{ "Hit me!","Add a word" };

	string t_practice = "Do you know the meaning of the following word?";
	string o_practice[]{ "I think so.. tell me!" };
	
	string t_gotit = "Did you get it right?";
	string o_gotit[]{ "Yes! got it!", "Messed it up :(" };

	// Display main menu
	this->ui->displayMenu(t_mainmenu,o_mainmenu, 2, true);
	
	string choice = this->ui->getString();
	
	// Keeps the app in MM until exit has been typed
	while (choice != "exit") {
		int n_choice = stoi(choice);

		// Parse user choice from main menu
		switch (n_choice)
		{
		case 1: {
			try {
				// This will throw an exception if no words have been entered
				word w = this->getWord();

				// Display a word and wait
				this->ui->displayMenu(t_practice + "\n" + w.original, o_practice, 1);
				int n_choice = stoi(this->ui->getString());

				// User wants to continue
				if (n_choice == 1) {

					// Show translation and ask the user if they got it right
					this->ui->output(w.original + " means: " + w.translation);
					this->ui->displayMenu(t_gotit, o_gotit, 2);
					int n_choice = stoi(this->ui->getString());

					switch (n_choice)
					{
					// User got it right
					case 1:
						w.bingos++;
						w.tries++;
						this->answered_correctly->push_back(w);
						break;
						// User fucked it up
					case 2:
						w.tries++;
						// put the word back to the queue
						this->pushWord(w);
						break;
					// user is having a stroke
					default:
						this->ui->output("Please enter a valid choice!");
						break;
					}
				}
				// invalid choice
				else {
					this->ui->output("Please enter a valid choice!");
					Sleep(2000);
				}
			}
			// queue is empty
			catch (const std::exception&) {
				this->ui->output("Word database is empty!");
				Sleep(2000);
			}
			break;
		}
		// The user has chosen to enter a new word
		case 2: {
			this->ui->output("Please write a word in German:");
			string org = this->ui->getString();

			this->ui->output("Please enter the word " + org + " in English:");
			string trans = this->ui->getString();

			word w(org, trans);
			this->pushWord(w);
			this->ui->output("The word " + org + " has been successfully entered to the database");
			break;
		}
		// invalid choice in main menu
		default:
			this->ui->output("Please enter a valid choice!");
			break;
		}

		Sleep(2000);
		// redraw main menu and wait for user action
		this->ui->displayMenu(t_mainmenu, o_mainmenu, 2,true);
		choice = this->ui->getString();
	}
	this->writeToFile(filename);
}


/**
* Returns a copy of the word on top of queue, and removes it.
*/
trainer::word trainer::getWord()
{
	if (this->words->empty())
		throw exception();
	// copy the word on top 
	word w = this->words->top();

	// remove it from queue
	this->words->pop();

	// return a copy
	return w;
}

void trainer::pushWord(const word & w)
{
	this->words->push(w);
}

void trainer::writeToFile(string filename) {
	ofstream out_file(filename);

	if (!out_file.is_open()) {
		throw exception();
	}

	while (!this->words->empty()) {
		// get word from the queue
		word w = this->words->top();
		
		// write its string representation to file
		out_file << w.to_string() << endl;

		// remove word from queue
		this->words->pop();
	}

	while (!this->answered_correctly->empty()) {
		// get word from vector
		word w = this->answered_correctly->back();

		// write its string representation to file
		out_file << w.to_string() << endl;
		
		// remove word from queue
		this->answered_correctly->pop_back();
	}

	out_file.close();

}

void trainer::loadFromFile(string filename) {

	ifstream inFile(filename);	

	if (!inFile.is_open()) {
		return;
	}

	std::string line;

	// load each word to queue
	while (std::getline(inFile, line)) {
		string* values = split(',', line);

		word w(values[0], 
			   values[1], 
			   stod(values[2]), 
			   stod(values[3]));
		this->words->push(w);
	}
		
	inFile.close();
}


string* trainer::split(char c, const string& str) {
	// first count the number of times the delimeter char appears in the string
	// to determine the size of the output array.
	int numOfChars = 0;
	int right = str.find(c);
	int left = 0;

	while (right != string::npos) {
		numOfChars++;
		left = right;
		right = str.find(c, left + 1);
	}

	// number of delimiters + 1 = number of values
	string* frags = new string[numOfChars + 1];

	// cut the values in between the delimiters
	// right boundary = the next delimeter
	// left boundary = prev  right boundary + 1	
	right = str.find(c);
	left = 0;

	int i = 0;
	for (; i < numOfChars; i++) {
		frags[i] = str.substr(left, right - left);
		left = right + 1;
		right = str.find(c, left);
	}

	// cut last value until the end (no more delimeters)
	frags[i] = str.substr(left);

	return frags;
}
