#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "mystring.h"
#include <string>

using namespace stringexercise;

mystring str;
mystring str1("Hello");
mystring str2(" world!");
mystring str3(*(new mystring("cpy constructor")));
mystring str4(*(new std::string("from std::string!")));

TEST_CASE("constructors") {
	REQUIRE(str.length() == 0);
	REQUIRE(str1.length() == 5);
	REQUIRE(str2.length() == 7);
	REQUIRE(str3.length() == 15);
	REQUIRE(str4.length() == 17);
}
