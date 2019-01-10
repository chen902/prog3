#include "mystring.h"

using namespace stringexercise;

// A standard default constructor
mystring::mystring()
{
	this->capacity = DEFAULT_CAPACITY;
	this->occupied = 0;
	this->sequence = new char[DEFAULT_CAPACITY];
	this->sequence[0] = '\0';
}

// construction of a mystring object with a string literal (c_string)
stringexercise::mystring::mystring(const char str[])
{
	// allocate 120% of the needed amount of bytes. or DEFAULT_CAPACITY if needed amount is 0
	size_t required = static_cast<size_t>(strlen(str) * CAPACITY_DELTA);
	this->capacity = required == 0 ? DEFAULT_CAPACITY : required;
	
	this->occupied = std::strlen(str);
	this->sequence = new char[this->capacity];
	std::strcpy(this->sequence, str);
}

// constructor from std::string, calles the c string constructor
stringexercise::mystring::mystring(const std::string str) : mystring(str.c_str()) {}

// constructor from mystring, calles the c string constructor
stringexercise::mystring::mystring(const mystring & source) : mystring(source.c_str()){}

// destructor - releases memory helf by sequence
mystring::~mystring()
{
	delete[] this->sequence;
}

// concatenation operator for mystring object, calles the c_string variation
mystring & stringexercise::mystring::operator+=(const mystring & addend)
{
	return *this += addend.c_str();
}

// concatenates a c string to the calling mystring object
mystring & stringexercise::mystring::operator+=(const char addend[])
{
	// required size after concatenation
	size_t required = static_cast<size_t>((this->occupied + strlen(addend)) * CAPACITY_DELTA);

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

// concatenates a single character to the calling mystring, uses the c_string variation
mystring & stringexercise::mystring::operator+=(const char addend)
{
	return *this += &addend;
}

// Assignment operator, resets the sequence and appends the source object, using the += operator
mystring & stringexercise::mystring::operator=(const mystring & source)
{
	// discard the current sequence
	this->sequence[0] = '\0';
	this->occupied = strlen(this->sequence);
	
	// append the new sequence
	return *this += source;
}

// Const subscription operator
const char & stringexercise::mystring::operator[](size_t position) const
{
	if (position < 0 || position >= this->occupied)
		throw std::out_of_range("Index out of bounds!");

	return this->sequence[position];
}

// Non-const subscription operator
char & stringexercise::mystring::operator[](size_t position)
{
	if (position < 0 || position >= this->occupied)
		throw std::out_of_range("Index out of bounds!");

	return this->sequence[position];
}

// Swapping two string simply by swapping the state of the objects
void stringexercise::mystring::swap(mystring& other)
{
	size_t tCapacity = other.capacity;
	size_t tOccupied = other.occupied;
	char* tSeq = other.sequence;

	other.capacity = this->capacity;
	other.occupied = this->occupied;
	other.sequence = this->sequence;

	this->capacity = tCapacity;
	this->occupied = tOccupied;
	this->sequence = tSeq;
}

// A helper that resizes the char sequence to a given size 
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
	outs << source.c_str();
	return outs;
}

std::istream & stringexercise::operator>>(std::istream & ins, mystring & target)
{
	mystring newstr;

	char c = (char)ins.get();

	// read input stream until <br> or -1 which appears at the end of a stream......
	while (c != -1 && c != '\n') {
		newstr += c;
		c = (char)ins.get();
	}
	target = newstr;

	return ins;
}

// Returns a new mystring object containing a concatenation of the two objects sent 
mystring stringexercise::operator+(const mystring & s1, const mystring & s2)
{
	return mystring(s1) += s2;
}

// Returns a new mystring object containing a concatenation of a mystring object and a c_string
mystring stringexercise::operator+(const mystring & s1, const char * s2)
{
	return mystring(s1) += s2;
}

// Returns a new mystring object containing a concatenation of a c_string  and a mystring object
mystring stringexercise::operator+(const char * s1, const mystring & s2)
{
	return mystring(s1) += s2;
}

// compares two mystring objects using strcmp()
bool stringexercise::operator==(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) == 0;
}

// compares two mystring objects using strcmp()
bool stringexercise::operator!=(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) != 0;
}

// compares two mystring objects using strcmp()
bool stringexercise::operator>=(const mystring & s1, const mystring & s2)
{
	int result = strcmp(s1.sequence, s2.sequence);
	return  result == 0 || result == 1 ;
}

// compares two mystring objects using strcmp()
bool stringexercise::operator<=(const mystring & s1, const mystring & s2)
{
	int result = strcmp(s1.sequence, s2.sequence);
	return  result == 0 || result == -1;
}

// compares two mystring objects using strcmp()
bool stringexercise::operator>(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) == 1;
}

// compares two mystring objects using strcmp()
bool stringexercise::operator<(const mystring & s1, const mystring & s2)
{
	return strcmp(s1.sequence,s2.sequence) == -1;
}
