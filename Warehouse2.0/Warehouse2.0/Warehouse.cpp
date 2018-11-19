/**@file:Warehouse.cpp
 * @Author: Chen Kasirer
 * The Warehouse class holds a vector of all stock items available. It is initialized from a file.
 */
#include <string>
#include <fstream>
#include <iostream>
#include "Warehouse.h"

using namespace std;

/**
 * Initializes the vector of stock items by reading the warehouse input file with the name
 * given as input.
 */
void Warehouse::init_from_file(std::string filename) {
	fstream in_file(filename);

	// In case file was not opened successfully
	if (!in_file.is_open()) {
		cout << "Error opening file " + filename << endl;
		return;
	}

	string line;

	// Get and discard first line (headers)
	getline(in_file, line);

	// Read the file line by line
	while (getline(in_file, line)) {
		
		// an array of strings where each cell is an individual value. 
		string* values = split(',', line);

		// initializes a stock object using the information obtained from the file
		Stock* s = new Stock(
			stoi(values[ARTICLE_ID]), 
			stof(values[PRICE]), 
			stoi(values[SUPPLY_TIME]), 
			values[DESCRIPTION], 
			stoi(values[IN_STOCK]), 
			stoi(values[MAX_STOCK]), 
			stoi(values[DAILY_CONSMPTION]));

		// adds to the back of the vector
		this->items_in_stock.push_back(s);
	}

	in_file.close();
}

/**
 * Writes the comma delimited string representation of the warehouse to an output file.
 */
void Warehouse::write_to_file(std::string filename) {
	ofstream out_file(filename);

	if (!out_file.is_open()) {
		cout << "Error opening file " + filename << endl;
		return;
	}

	// Writes the CSV headers line
	string headers = "ID,Description,Price,Supply Time,Actual Stock,Maximum Stock,Daily Consumption,Reorder Amount,Order Proposal";
	out_file << headers << endl;

	out_file << this->to_string();

	out_file.close();
}

/**
 * Splits a given string to an array of strings using a provided delimited 'c'. python style.
 */
std::string* Warehouse::split(char c, std::string str) {
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
	string *frags = new string[numOfChars + 1];

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
 * Returns a comma delimited string representation of the entire warehouse stock.
 * It iterates over the stock items vector and appending the to_string() output from each stock item.
 * It prints an additional line stating the overall value of the stock in the warehouse.
 */
string Warehouse::to_string() {
	string output;
	float total_stock_value = 0;
	
	// this->items_in_stock is a vector of object of type Stock*
	// item is a pointer to the currently iterated item so has to be 
	// dereferenced once in order to obtain the pointer to Stock.
	for (vector<Stock*>::iterator item = this->items_in_stock.begin();
		item != this->items_in_stock.end();
		++item) {

		output += (*item)->to_string() + '\n';		
		total_stock_value += (*item)->get_stock_value();
	}

	output += "Total stock value in warehouse is: " + std::to_string(total_stock_value) + " euros.\n";

	return output;
}