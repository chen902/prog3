/**@file:main.cpp
 * @Author: Chen Kasirer
 * This program initializes a warehouse object form an input file, 
 * and writes a csv representation of the warehouse with additional information
 * as defined in exercise 3.
 */

#include "Article.h"
#include "Stock.h"
#include "Warehouse.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	
	Warehouse warehouse;

	// Reads the input file and initializes all items and their stock information
	warehouse.init_from_file("warehouse.csv");

	// Writes warehouse stock information to file
	warehouse.write_to_file("warehouse_output.csv");

	return 0;
}