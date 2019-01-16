/**@file  trainer.cpp
 * Author: Chen Kasirer
 *
 * Created on Januray 16, 2019
 *
 * The trainer class is the main class of the vocabulary trainer, it contains all logic.
 * This vocabulary trainer is statistics based, and at its core a priority_queue is used.
 * Words are ranked based on the ration between the number of attempts and the number of successfull attempts.
 * The more the user gets a word wrong, the more often it'll appear at the top of the queue.
 * 
 * After indicating that a word was correctly translated, its statistics are updated and it is removed from the queue and moved recorded in a vector. 
 * After indicating that a word was incorrectly translated, its statistics are updated and it is put back to the queue. Depending on its statistics, 
 * it might appear again immidiately.
 */

#include "trainer.h"

using namespace std;

/**
 * The vocabulary is initialized from a file, if it exists. 
 */
trainer::trainer(string filename) : ui()
{
	this->filename = filename;
	
	// Allocate memory for the priority queue and vector
	this->words = new priority_queue<word, vector<word>, WordCompare>();
	this->answered_correctly = new vector<word>();

	// Read words from file if it exists
	this->loadFromFile(filename);
}


/**
 * Dtor, releases memory of used data structures
 */
trainer::~trainer()
{
	delete this->ui;
	delete this->words;
	delete this->answered_correctly;
}

/**
 * This function is the main loop of the trainer, calls all other functionality 
 */
void trainer::start()
{
	string t_mainmenu = "Welcome to Vocabu-hell!";
	string o_mainmenu[]{ "Hit me!","Add a word" };

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
			this->practice();
			break;
		}
		// The user has chosen to enter a new word
		case 2: {
			this->enterNewWord();
			break;
		}
		// invalid choice in main menu
		default:
			this->ui->output("Please enter a valid choice!");
			break;
		}

		Sleep(this->SLEEP_TIME);
		// redraw main menu and wait for user action
		this->ui->displayMenu(t_mainmenu, o_mainmenu, 2,true);
		choice = this->ui->getString();
	}
}

/**
 * This function handles the routine for adding a new word to the vocabulary
 */
void trainer::enterNewWord() {
	this->ui->output("Please write a word in German:");
	string org = this->ui->getString();

	this->ui->output("Please enter the word " + org + " in English:");
	string trans = this->ui->getString();

	word w(org, trans);
	this->pushWord(w);
	this->ui->output("The word " + org + " has been successfully entered to the database");
}

/**
 * This function handles the routine for practicing a word. A word is feched from the top of the queue and displayed to the user.
 * they are then displayed the translation, and prompted to say if they got it right, which is recoded on the statistics of each word.
 */
void trainer::practice() {
	string t_practice = "Do you know the meaning of the following word?";
	string o_practice[]{ "I think so.. tell me!" };

	try {
		// This will throw an exception if no words have been entered
		word w = this->getWord();

		// Display a word and wait
		this->ui->displayMenu(t_practice + "\n" + w.original, o_practice, 1);
		int n_choice = stoi(this->ui->getString());

		// User wants to continue
		if (n_choice == 1) {
			this->showSolution(w);
		}
		// invalid choice
		else {
			this->ui->output("Please enter a valid choice!");
			Sleep(this->SLEEP_TIME);
		}
	}
	// queue is empty
	catch (const std::exception&) {
		this->ui->output("Word database is empty!");
		Sleep(this->SLEEP_TIME);
	}

}

/**
 *	Handles the routing showing the user the right answer, and lets them choose if they got it right or not.
 */
void trainer::showSolution(word& w) {
	string t_gotit = "Did you get it right?";
	string o_gotit[]{ "Yes! got it!", "Messed it up :(" };

	// Show translation and ask the user if they got it right
	this->ui->output(w.original + " means: " + w.translation);
	this->ui->displayMenu(t_gotit, o_gotit, 2);
	int n_choice = stoi(this->ui->getString());

	switch (n_choice)
	{
		// User got it right
	case 1:
		this->handleBingo(w);
		break;
		// User fucked it up
	case 2:
		this->handleMiss(w);
		break;
		// user is having a stroke
	default:
		this->ui->output("Please enter a valid choice!");
		break;
	}
}

/**
 * Updates the statistics of a word in case of a correct answer
 */
void trainer::handleBingo(word& w) {
	w.bingos++;
	w.tries++;
	this->answered_correctly->push_back(w);
	this->ui->output("Well done!");
}

/**
 * Updates the statistics of a word in case the user did not know the answer
 */
void trainer::handleMiss(word& w) {
	w.tries++;
	// put the word back to the queue
	this->pushWord(w);
	this->ui->output("Better luck next time!");
}

/**
 * Returns a copy of the word from the top of queue, and removes it.
 */
word trainer::getWord()
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

/**
 * Pushes a word into the priority queue
 */
void trainer::pushWord(const word & w)
{
	this->words->push(w);
}

/**
 * Writes the content of the priority queue and the correctly answered words vector to a file.
 */
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

/**
 * Loads the vocabulary from a file, if it exists
 */
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

/**
 * Borrowed from the Warehouse assignment. Gets a comma delimited string and returns an array containing each of the 
 * separate values.
 */
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

/**
 * Should be called before terminating the program in order to any new words of statistics to a file.
 */
void trainer::end() {
	this->writeToFile(filename);
}
