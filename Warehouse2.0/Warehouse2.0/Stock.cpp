/**@file:Stock.cpp
 * @Author: Chen Kasirer
 * The stock class holds the stock information related to an article.
 */
#include <string>
#include "Stock.h"
#include "Article.h"

 /**
  * Constructor for an item (Stock) object. Initializes an instance of article as well as 
  * an instance of Stock containing the stock information for this article.
  */
Stock::Stock(
	int id, 
	float cost, 
	int supply_time, 
	std::string desc, 
	int in_stock, 
	int max_stock, 
	int consumption) 
	
	// Initializing composed Article member
	: article(id,cost,supply_time,desc){
	
	this->amount_in_stock = in_stock;
	this->max_in_stock = max_stock;
	this->daily_consumption = consumption;
}

/**
 * A getter for the amount of article in stock.
 */
int Stock::get_amount_instock() {
	return this->amount_in_stock;
}

/**
 * A getter for the maximum amount of article in stock.
 */
int Stock::get_max_instock() {
	return this->max_in_stock;
}

/**
 * A getter for the daily consumption of this item.
 */
int Stock::get_daily_consumption() {
	return this->daily_consumption;
}

/**
 * Calculates the threshold amount of articles that indicates the need to refill stock,
 * taking into account a RESERVE number of days.
 */
int Stock::get_reorder_amount() {
	return (this->article.get_supply_time() + RESERVE) * this->daily_consumption;
}

/**
 * Determines whether or not an article has reached the point where it needs to be reordered.
 * It compares the current amount of items in stock with the previously calculated reorder amount.
 */
std::string Stock::orderProposal() {
	if (this->amount_in_stock <= this->get_reorder_amount()) {
		return "Yes";
	}	else {
		return "No";
	}
}

/*
 * Returns the stock value for this item, by multiplying the item unit price and the number of items currently in stock.
 */
float Stock::get_stock_value() {
	return this->amount_in_stock * this->article.get_cost();
}

/*
 * Returns a string representation of this stock item, including the article specific information.
 * Calls the to_string() method of the corresponding article.
 */
std::string Stock::to_string() {
	return this->article.to_string() +
		std::to_string(this->amount_in_stock)
		+ ',' + std::to_string(this->max_in_stock)
		+ ',' + std::to_string(this->daily_consumption)
		+ ',' + std::to_string(this->get_reorder_amount())
		+ ',' + this->orderProposal();
}
