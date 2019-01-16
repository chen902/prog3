#pragma once
#include "ui.h"
#include "word.h"
#include <string>
#include <queue>
#include <map>
#include <Windows.h>
#include <fstream>

using namespace std;

class trainer
{
public:

	class WordCompare {
	public:
		bool operator()(const word& w1, const word& w2) {
			return (w1.bingos / w1.tries) > (w2.bingos / w2.tries);
		}
	};

	trainer(string filename = "wordbank.csv");
	~trainer();

	void start();
	void end();


private:
	string filename;
	ui* ui;
	priority_queue<word,vector<word>,WordCompare>* words;
	vector<word>* answered_correctly;

	word getWord();
	void pushWord(const word& w);
	void loadFromFile(string filename);
	void writeToFile(string filename);
	void practice();
	void enterNewWord();
	void handleBingo(word& w);
	void handleMiss(word& w);
	void showSolution(word& w);
	string* split(char c, const string& str);
};