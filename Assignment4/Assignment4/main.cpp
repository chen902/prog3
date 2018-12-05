/**@file:main.cpp
 * @Author: Chen Kasirer
 * Programming 3 - Assignment 4 
 */
#include <iostream>
#include <string>
#include <random>
#include "Vector.h"

using namespace std;

int main() {
	// random content generation
	double lower_bound = 0;
	double upper_bound = 100;
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;

	int numberOfVectors = 5;

	// an array of pointers to Vector objects (prevents unnecessary initialization of the objects)
	Vector** arr = new Vector*[numberOfVectors];

	// generates 20 vectors in R3 with random values
	for(int i=0; i<numberOfVectors; ++i){
		double x = unif(re);
		double y = unif(re);
		double z = unif(re);

		// pointer to a new Vector object
		arr[i] = new Vector(3);
		
		// non-const subscription operator
		(*arr[i])[0] = x;
		(*arr[i])[1] = y;
		(*arr[i])[2] = z;
	}

	// prints the vectors
	for (int i = 0; i < numberOfVectors; ++i) {
		cout << *arr[i] << endl;
	}

	// releasing memory
	for (int i = 0; i < numberOfVectors; ++i) {
		delete arr[i];
	}
	

	Vector v1;
	Vector v2;
	Vector v3;

	v1[0] = 1.0;
	v1[1] = 2.5;
	v2[0] = 3.0;
	v2[1] = 4.5;
	v3[0] = 5.0;
	v3[1] = 6.5;

	// ostream operator chaining
	cout << v1 << v2 << v3 << endl;
	
	// deep copy on assignment
	v1 = v2;
	
	v2[0] = 3.5;
	
	// deep copy using copy constructor
	Vector v4 = v3;

	v3[0] = 5.5;

	cout << v1 << v2 << v3 << v4 << endl;
	
	// index out of bounds exception
	try {
		v1[3] = 12.3;
	}
	catch(std::out_of_range e){
		cout << e.what() << endl;
	}
	

	cin.sync();
	cin.get();
}