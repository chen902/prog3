/**@file:Article.h
 * @Author: Chen Kasirer
 * The stock class holds the stock information related to an article.
 */
#pragma once

#include <iostream>

class Article {
private:
	int article_id;
	float unit_cost;
	int supply_time;
	std::string description;

public:
	Article(int id, float cost, int supply_time, std::string desc);

	int get_id();
	float get_cost();
	int get_supply_time();
	std::string get_description();
	
	std::string to_string();
};