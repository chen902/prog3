/**@file:Article.cpp
 * @Author: Chen Kasirer
 * The stock class holds the stock information related to an article.
 */
#include <string>
#include "Article.h"

using namespace std;

/**
 * Constructor for an article object.
 */
Article::Article(int id, float cost, int supply_time, std::string desc) {
	this->article_id = id;
	this->unit_cost = cost;
	this->supply_time = supply_time;
	this->description = desc;
}

/**
 * A getter for this article's ID.
 */
int Article::get_id() {
	return this->article_id;
}

/**
 * A getter for this article's unit cost.
 */
float Article::get_cost() {
	return this->unit_cost;
}

/**
 * A getter for this article's supply time.
 */
int Article::get_supply_time() {
	return this->supply_time;
}

/**
 * A getter for this article's description
 */
std::string Article::get_description() {
	return this->description;
}

/**
 * Returns a string representation of this article in comma delimited format.
 */
std::string Article::to_string() {
	return std::to_string(this->article_id) 
		+ ',' + this->description 
		+ ',' + std::to_string(this->unit_cost) 
		+ ',' + std::to_string(this->supply_time) 
		+ ',';
}
