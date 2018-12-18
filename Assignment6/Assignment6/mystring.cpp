#include "mystring.h"

using namespace stringexercise;

// A standard default constructor
mystring::mystring()
{
	std::cout << "mystring default constructor" << std::endl;
	this->capacity = this->DEFAULT_CAPACITY;
	this->occupied = 0;
	this->sequence = new char[DEFAULT_CAPACITY];
	this->sequence[0] = '\0';
}

// construction of a mystring object with a sting literal (c_string)
stringexercise::mystring::mystring(const char str[])
{
	std::cout << "c_string constructor called" << std::endl;
	this->capacity = static_cast<size_t>(std::strlen(str) * this->CAPACITY_DELTA);
	this->occupied = std::strlen(str);
	this->sequence = new char[this->capacity];
	std::strcpy(this->sequence, str);
}

stringexercise::mystring::mystring(const std::string str) : mystring(str.c_str()) { std::cout << "string constructor called" << std::endl; }

stringexercise::mystring::mystring(const mystring & source) : mystring(source.c_str()){ std::cout << "mystring constructor called" << std::endl; }

mystring::~mystring()
{
	delete[] this->sequence;
}

mystring & stringexercise::mystring::operator+=(const mystring & addend)
{
	return *this += addend.c_str();
}

mystring & stringexercise::mystring::operator+=(const char addend[])
{
	// required size after concatenation
	size_t required = static_cast<size_t>((this->occupied + strlen(addend)) * this->CAPACITY_DELTA);

	// a resize is due 
	if (required > this->capacity) {
		this->resize(required);
	}

	// concatenate strings
	strcat(this->sequence, addend);
	//this->capacity = required;
	this->occupied = strlen(this->sequence);

	return *this;
}

mystring & stringexercise::mystring::operator+=(const char addend)
{
	return *this += &addend;
}

mystring & stringexercise::mystring::operator=(const mystring & source)
{
	// discard the current sequence
	this->sequence[0] = '\0';
	this->occupied = strlen(this->sequence);
	
	// append the new sequence
	return *this += source;
}
const char & stringexercise::mystring::operator[](size_t position) const
{
	if (position < 0 || position > this->occupied - 1)
		throw std::out_of_range("Index out of bounds!");

	return this->sequence[position];
}

char & stringexercise::mystring::operator[](size_t position)
{
	if (position < 0 || position > this->occupied - 1)
		throw std::out_of_range("Index out of bounds!");

	return this->sequence[position];
}

void stringexercise::mystring::swap(mystring &)
{
}


void stringexercise::mystring::resize(size_t size)
{
	// allocate memory for a new c_string
	char* newSequence = new char[size];

	// copy the old content
	strcpy(newSequence, this->sequence);

	// free memory of old c_string
	delete[] this->sequence;

	// update the pointer
	this->sequence = newSequence;
	this->capacity = size;
}

std::ostream & stringexercise::operator<<(std::ostream & outs, const mystring & source)
{
	outs << source.sequence;
	return outs;
}

std::istream & stringexercise::operator>>(std::istream & ins, mystring & target)
{
	mystring newstr;

	char c = (char)ins.get();

	// read input stream until <br>
	while (c != '\n') {
		newstr += c;
		c = (char)ins.get();
	}
	target = newstr;

	return ins;
}

mystring stringexercise::operator+(const mystring & s1, const mystring & s2)
{
	return mystring(s1) += s2;
}

mystring stringexercise::operator+(const mystring & s1, const char * s2)
{
	return mystring(s1) += s2;
}

mystring stringexercise::operator+(const char * s1, const mystring & s2)
{
	return mystring(s1) += s2;
}

bool stringexercise::operator==(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) == 0;
}

bool stringexercise::operator!=(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) != 0;
}

bool stringexercise::operator>=(const mystring & s1, const mystring & s2)
{
	int result = strcmp(s1.sequence, s2.sequence);
	return  result == 0 || result == 1 ;
}

bool stringexercise::operator<=(const mystring & s1, const mystring & s2)
{
	int result = strcmp(s1.sequence, s2.sequence);
	return  result == 0 || result == -1;
}

bool stringexercise::operator>(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) == 1;
}

bool stringexercise::operator<(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) == -1;
}
