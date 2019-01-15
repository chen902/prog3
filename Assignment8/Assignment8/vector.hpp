/**@file:Vector.hpp
 * @Author: Chen Kasirer
 * A generic container implementation of the vector class. Allows the vector to contain any type.
 */

#pragma once
#include <iostream>
#include <sstream>

template <class T>
class Vector {
	
private:
	int dimension;
	T * data;

	void resize(int size);
public:
	// Ctors & Dtor
	Vector();
	Vector(int dimesion,T init_value);
	Vector(const Vector &obj);
	~Vector();

	void init_with_vector(const Vector<T>& other);
	int size() const;
	void insert(int index, const T& value);
	void insert(int index, const Vector<T>& v);
	void remove(int index);
	std::string to_string() const;

	// operator overloadings 
	T& operator[](int index);
	const T& operator[](int index) const;
	void operator=(const Vector<T>& obj);

	// friends declerations
	template <class T>
	friend void swap(Vector<T> &v1, Vector<T> &v2);
};

/**
 * Ctors and Dtor
 */
template<class T>
Vector<T>::Vector() {
	this->data = new T[0];
	this->dimension = 0;
}

/**
 * Default constructor. initializes and empty vector.
 */
template<class T>
Vector<T>::Vector(int dimension,T init_value){
	this->data = new T[dimension];
	this->dimension = dimension;
	
	for (int i = 0; i < dimension; ++i) {
		this->data[i] = init_value;
	}
}

/**
 * Copy constructor. Allow a creation of a new Vector object using the data contained in an existing one.
 * A deep copy is required in that case due to the runtime allocated array of the data.
 */
template<class T>
Vector<T>::Vector(const Vector &obj) {
	this->init_with_vector(obj);
}

/**
 * Destructor.
 * Required in order to release the memory held by the array of coordinates when deleting an instance of Vector.
 */
template <class T>
Vector<T>::~Vector() {
	delete[] this->data;
}

/**
 * helper function for the initialization of a vector using content of another vector
 */
template <class T>
void Vector<T>::init_with_vector(const Vector<T>& other) {
	// copy dimension
	this->dimension = other.dimension;

	// allocate memory for a new coordinates array
	this->data = new T[other.dimension];

	// copy coordinates
	for (int i = 0; i < other.dimension; ++i) {
		this->data[i] = other[i];
	}
}

/**
 * returns the size of the vector
 */
template<class T>
inline int Vector<T>::size() const
{
	return this->dimension;
}

/**
 * inserts a value in the given index. content will be shifted to the left
 */
template<class T>
void Vector<T>::insert(int index, const T& value)
{
	Vector<T> * t = new Vector<T>(1, value);
	this->insert(index, *t);
}

/**
 * inserts the content from another vector into this vector
 */
template<class T>
void Vector<T>::insert(int index, const Vector<T>& v)
{
	// if requested index is out of bounds of the destination array then throw exception
	if (index < 0 || (index > v.dimension - 1 && v.dimension !=0)) {
		throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds!");
	}

	//resize destincation vector if not enough space
	int reqSize = this->size() + v.size();
	this->resize(reqSize);

	// shift left the old content if necessary
	for (int i = index; i < this->dimension - v.size(); ++i) {
		this->data[i + v.size()] = this->data[i];
	}

	// copy contents of second vector
	for (int i = index; i < index + v.size(); ++i) {
		this->data[i] = v[i-index];
	}
}

/**
 * removes an element from the requested index. the gap is closed by right shifting the elements.
 * the vector is then downsized.
 */
template<class T>
void Vector<T>::remove(int index)
{
	// if requested index is out of bounds of the destination array then throw exception
	if (index < 0 || (index > this->dimension - 1 && this->dimension != 0)) {
		throw std::out_of_range("Index " + std::to_string(index) + " is out of bounds!");
	}
	int newSize = this->dimension-1;

	// if it's the last item, resize(0) will just release the memory
	if(newSize != 0){
		// shifts all the elements to the right of the removed index
		// resize will resize the vector, discarding the last element
		for (int i = index + 1; i < this->dimension; ++i) {
			this->data[i - 1] = this->data[i];
		}
	}

	this->resize(newSize);
}


/**
 * returns a string representation of the elements of the vector.
 * element types are expected to implement the output stream operator.
 */
template <class T>
std::string Vector<T>::to_string() const {
	std::stringstream output;
	output << "(";

	for (int i = 0; i < this->dimension-1; ++i) {
		output << this->data[i] << ",";
	}
	
	if (this->dimension != 0){
		output << this->data[this->dimension - 1];
	}
	
	output << ")";

	return output.str();
}

/**
 * a private helper method that resizes the vector to the request size.
 * when enlarging, the old content is copied to the start of the new vector.
 * when shrinkink, the end will be discarded.
 */
template<class T>
void Vector<T>::resize(int size)
{
	// new memory allocation
	T* temp = new T[size];
	
	// required in order to copy the only the old content
	int min = size <= this->dimension ? size : this->dimension;
	
	// copy values from the original array to the new size
	// as much as possible
	for (int i = 0; i < min; ++i) {
		temp[i] = this->data[i];
	}

	// release old memory allocation
	delete[] this->data;

	this->data = temp;
	this->dimension = size;
}

/**
 * A non-const operator[] overload.
 * Given an 'index' a non-constans reference to a cell in the coordinates array will be returned.
 * This may be used to retrive a cell in order to assign a value to it.
 * If the index is out of array bounds, an exception stating the given index will be thrown.
 */
template <class T>
T& Vector<T>::operator[](int index) {
	if (index < 0 || index >= this->dimension) {
		throw std::out_of_range("Index " + std::to_string(index) + " out of range!");
	}
	return this->data[index];
}

/**
 * A const operator[] overload.
 * Given an 'index' a const reference to cell in the coordinates array will be returned.
 * this may be used to retrive the content of a cell that shall not be modified.
 * If the index is out of array bounds, an exception stating the given index will be thrown.
 */
template <class T>
const T& Vector<T>::operator[](int index) const {
	if (index < 0 || index >= this->dimension) {
		throw std::out_of_range("Index " + std::to_string(index) + " out of range!");
	}
	return this->data[index];
}

/**
 * assignment operator overload, performes deep copy
 */
template <class T>
void Vector<T>::operator=(const Vector<T>& obj) {
	this->init_with_vector(obj);
}

/**
 * Non member functions
 */

/**
 * swaps two vectors by swapping pointers and administrative data
 */
template <class T>
void swap(Vector<T> &v1, Vector<T> &v2) {
	// save pointer to v1 data
	T* data = v1.data;
	int size = v1.dimension;

	// set data of v1 to point to data of v2
	v1.data = v2.data;
	v1.dimension = v2.dimension;

	// set data of v2 to point to data of v1
	v2.data = data;
	v2.dimension = size;
}

/**
 * output stream operator overloading for class Vector<T>
 */
template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& obj) {
	os << obj.to_string();
	return os;
}
