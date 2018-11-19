/**@file:Stock.h
 * @Author: Chen Kasirer
 * The stock class holds the stock information related to an article.
 */

#pragma once
#include <iostream>
#include "Article.h"

class Stock {
private:
	Article article;
	int amount_in_stock;
	int max_in_stock;
	int daily_consumption;
	const int RESERVE = 2;

	int get_reorder_amount();
	std::string orderProposal();

public:
	Stock(int id, float cost, int supply_time, std::string desc, int in_stock, int max_stock, int consumption);

	int get_amount_instock();
	int get_max_instock();
	int get_daily_consumption();
	float get_stock_value();

	std::string to_string();
};