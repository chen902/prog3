/**@file:Vector.h
 * @Author: Chen Kasirer
 * Vector class represents a linera algebra structure vector.
 */
#pragma once
#include <iostream>

class Vector {

private:
	int dimension;
	double * coordinates;
	void init_with_vector(const Vector& other);
	

public:
	// Constructor
	Vector(int dimension=2, double init_value=0.0);
	
	// Copy constructor
	Vector(const Vector &obj);
	
	// Destructor
	~Vector();
	void set_value(int index, double value);
	std::string to_string() const;
	const double& get_value(int index) const;
	double& operator[](int index);
	const double& operator[](int index) const;
	void operator=(const Vector& obj);
};

std::ostream& operator<<(std::ostream& os, const Vector& obj);
std::string double_to_string(double const& d);