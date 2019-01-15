#pragma once
#include "ui.h"
#include <string>
#include <queue>
#include <map>

using namespace std;

class trainer
{
public:
	class userChoice {
	public:
		string name;
		void (*f);

		userChoice(string name, void* f) {
			this->name = name;
			this->f = f;
		}
	};

	class screen {
	public:
		string title;
		vector<userChoice>* options;
		
		
		screen(string title, vector<userChoice>* options) {
			this->title;
			this->options = options;
		}
	};

	trainer();
	~trainer();

	void start();
	void initialize();

	void practice();
	void addWord();
	void exit();
	void gotIt();
	void wrong();

	// get's a screen, displays it's options, and invokes function assigned to the option selected 
	void promptUser(string screen);

	class word {
		string original;
		string translation;
		int tries;
		int bingos;
	};


private:
	ui* ui;
	priority_queue<word> words;
};

