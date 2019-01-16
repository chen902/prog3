#pragma once
#include "ui.h"
#include <string>
#include <queue>
#include <map>
#include <Windows.h>
#include <fstream>

using namespace std;

class trainer
{
public:
	class word {
	public:
		string original;
		string translation;
		double tries;
		double bingos;

		word(const word& w) : original(w.original), translation(w.translation),tries(w.tries),bingos(w.bingos) {};
		word(const string& org, const string& trans, double tries, double bingos) :
			original(org), translation(trans) {
			tries = tries; bingos = bingos;
		};

		word(const string& org, const string& trans) :
			original(org), translation(trans) {
			tries = 1; bingos = 1;
		};

		string to_string() const {
			string output;
			output += this->original +"," 
				   + this->translation + "," 
					+ std::to_string(this->bingos) + ","
					+ std::to_string(this->tries);
			return output;
		};
	};

	class WordCompare {
	public:
		bool operator()(const word& w1, const word& w2) {
			return (w1.bingos / w1.tries) > (w2.bingos / w2.tries);
		}
	};

	trainer();
	~trainer();


	void start();
	word getWord();
	void pushWord(const word& w);
	void loadFromFile(string filename);
	void writeToFile(string filename);


private:
	ui* ui;
	priority_queue<word,vector<word>,WordCompare>* words;
	vector<word>* answered_correctly;

	string* split(char c, const string& str);
};