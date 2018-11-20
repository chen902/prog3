/**@file:Warehouse.h
 * @Author: Chen Kasirer
 * The Warehouse class holds a vector of all stock items available. It is initialized from a file.
 */
#pragma once

#include <iostream>
#include <vector>

#include "Stock.h"

class Warehouse {
private:
	
	// For the sake of readability, an enumeration is used to reference the file columns.
	enum columns {
		ARTICLE_ID = 0,
		DESCRIPTION = 1,
		IN_STOCK = 2,
		MAX_STOCK = 3,
		PRICE = 4,
		DAILY_CONSMPTION = 5,
		SUPPLY_TIME = 6
	};

	std::vector<Stock*> items_in_stock;
	
	static std::string* split(char c, std::string str);
public:
	void init_from_file(std::string filename);
	void write_to_file(std::string filename);
	std::string to_string();
};