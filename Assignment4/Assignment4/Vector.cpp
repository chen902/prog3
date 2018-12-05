/**@file:Vector.cpp
 * @Author: Chen Kasirer
 * Vector class represents a linera algebra structure vector.
 */
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Vector.h"

/*
 * Constructor. 
 * Initializes an object of type Vector with dimension and a default value 
 * for all coordinates. If any of the two is not provided, a default value will be provided 
 * from header file. (dimension=2, init_value=0).
 */
Vector::Vector(int dimension, double init_value) {
	std::cout << "normal constructor is called" << std::endl;
	this->dimension = dimension;
	this->coordinates = new double[dimension];
	for (int i = 0; i < dimension; ++i) {
		this->coordinates[i] = init_value;
	}
}

/*
 * Copy constructor. Allow a creation of a new Vector object using the data contained in an existing one.
 * A deep copy is required in that case due to the runtime allocated array of coordinates.
 */
Vector::Vector(const Vector &obj) {
	std::cout << "copy constructor is called" << std::endl;
	this->init_with_vector(obj);
}

/*
 * Destructor.
 * Required in order to release the memory held by the array of coordinates when deleting an instance of Vector.
 */
Vector::~Vector() {
	std::cout << "destructor is called" << std::endl;
	// Release memory used by the array
	delete[] this->coordinates;
}

/*
 * Gets the coordinate in the given index.
 * Uses the const operator[].
 */
const double& Vector::get_value(int index) const{
	return (*this)[index];
}

/*
 * Sets the coordinate in a certain index to the provided value.
 * Uses the non-const operator[].
 */
void Vector::set_value(int index, double value) {
	(*this)[index] = value;
}

/*
 * Returns a string representation of a vector object in the required format.
 * (x.xx, y.yy, z.zz)
 */
std::string Vector::to_string() const{
	std::string output = "(";
	
	// appends each of the coordinates to the string followed by a comma
	for (int i = 0; i < this->dimension-1; ++i) {
		output += double_to_string(this->coordinates[i]) + ", ";
	}
	
	// appends the last coordinate, followed by a closing bracket
	output += double_to_string(this->coordinates[this->dimension - 1]) + ")";

	// returns a copy of the string
	return  output;
}

/*
 * A non-const operator[] overload.
 * Given an 'index' a non-constans reference to a cell in the coordinates array will be returned.
 * This may be used to retrive a cell in order to assign a value to it.
 * If the index is out of array bounds, an exception stating the given index will be thrown.
 */
double& Vector::operator[](int index) {
	std::cout << "non const subsctiption is called" << std::endl;
	if (index < 0 || index >= this->dimension) {
		throw std::out_of_range("Index " + std::to_string(index) + " out of range!");
	}
	return this->coordinates[index];
}

/*
 * A const operator[] overload.
 * Given an 'index' a const reference to cell in the coordinates array will be returned.
 * this may be used to retrive the content of a cell that shall not be modified.
 * If the index is out of array bounds, an exception stating the given index will be thrown.
 */
const double& Vector::operator[](int index) const {
	std::cout << "constant subsctiption is called" << std::endl;
	if (index < 0 || index >= this->dimension) {
		throw std::out_of_range("Index " + std::to_string(index) + " out of range!");
	}
	return this->coordinates[index];
}

/*
 * An overload of the assignment operator.
 * This is necessary in order to perform a deep copy of the coordinates array when assigning.
 */
void Vector::operator=(const Vector& obj) {
	std::cout << "assignment subsctiption is called" << std::endl;
	this->init_with_vector(obj);
}

/*
 * Initializes this Vector from another vector using deep copy
 */
void Vector::init_with_vector(const Vector& other) {
	// copy dimension
	this->dimension = other.dimension;

	// allocate memory for a new coordinates array
	this->coordinates = new double[other.dimension];

	// copy coordinates
	for (int i = 0; i < other.dimension; ++i) {
		this->coordinates[i] = other[i];
	}
}

/*
 * A global helper function, used to convert a double to string with a fixed number of digits beyond the radix point.
 */
std::string double_to_string(double const& d) {
	std::stringstream sstr;
	sstr << std::fixed << std::setprecision(2) << d;
	return sstr.str();
}

/*
 * A global overloading of the << operator, allows sending a string representation of a vector
 * to an output stream, as well as appending it with other streams.
 */
std::ostream& operator<<(std::ostream& os, const Vector& obj) {

	os << obj.to_string();
	
	// allows chaining with other stream objects
	return os; 
}

