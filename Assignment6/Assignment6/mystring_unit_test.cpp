/**@file mystring_unit_testing.cpp
 * @brief unit testing using the Catch2 framework for the MyString project.
 *
 *
 * @author Leonhard Szerejko (Slight adaptations by Chen Kasirer)
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "mystring.h"
#include "sstream"

TEST_CASE("mystring behaves as a simple version of std::string", "[mystring]")
{
	//creation of mystring objects (unsing char array, char, char pointer and mystring objects)
	char arr[] = "abc"; //length 3

	//strcpy(arr, "abc");
	stringexercise::mystring* msArr = new stringexercise::mystring{ arr }; //"abc", length 3
	stringexercise::mystring* msString = new stringexercise::mystring("defghi"); //length 6
	stringexercise::mystring* msMs = new stringexercise::mystring{ *msArr }; //"abc", length 3
	stringexercise::mystring* msEmpty = new stringexercise::mystring; //"", length 0

	//some char* and char elements for use in sections
	char ch[10] = "abcdefghi";
	char ch2[5] = "abcz";
	char ch3 = 'z';

	SECTION("mystring objects are properly initialized with expected values on creation")
	{
		REQUIRE(msArr->length() == 3);
		REQUIRE(msMs->length() == 3);
		REQUIRE(msString->length() == 6);
		REQUIRE(msEmpty->length() == 0);
	}

	SECTION("mystring objects can be compared for all types of comparisons")
	{
		REQUIRE(*msArr == *msMs);
		REQUIRE(*msArr != *msString);
		REQUIRE(*msArr >= *msMs);
		REQUIRE(*msArr <= *msMs);
		REQUIRE(*msArr < *msString);
		REQUIRE(*msString > *msArr);

		SECTION("mystring objects can be compared with themselves")
		{
			REQUIRE(*msString == *msString);
		}
	}

	SECTION("mystring object can be assigned to each other")
	{
		*msEmpty = *msString;
		REQUIRE(*msEmpty == *msString);

		SECTION("mystring objects can be assigned to themselves")
		{
			*msString = *msString;
			REQUIRE(*msString == *msString);
		}

		SECTION("mystring object assignments can be chained")
		{
			*msEmpty = *msArr = *msMs;
			//delete msMs;
			
			REQUIRE(*msEmpty == *msMs);
			REQUIRE(*msArr == *msMs);
		}
	}

	SECTION("mystring objects can be manipulated using the index operator")
	{
		REQUIRE((*msArr)[0] == 'a');
		(*msArr)[0] = 'z';
		REQUIRE((*msArr)[0] == 'z');

		SECTION("index manipulations at illegal indexes are handled via an exception call")
		{
			REQUIRE_THROWS_AS((*msArr)[10], std::out_of_range);
			REQUIRE_THROWS_AS((*msEmpty)[0], std::out_of_range);
		}
	}

	SECTION("mystring objects can be manipulated with the addition assignment operator (+=) to append mystring, char* and char objects")
	{
		*msArr += *msString;
		REQUIRE(strcmp(msArr->c_str(), ch) == 0); //mystring+=mystring

		*msEmpty += ch;
		REQUIRE(strcmp(msEmpty->c_str(), ch) == 0); //empty mystring+=char*

		*msMs += ch3;
		REQUIRE(strcmp(msMs->c_str(), ch2) == 0); //mystring+=char

		SECTION("mystring objects will be resized in case of large additions")
		{
			*msEmpty = "";
			char ch4[100] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
			*msEmpty += ch4;
			REQUIRE(strcmp(msEmpty->c_str(), ch4) == 0);
		}
	}

	SECTION("mystring objects can be manipulated with the addition operator (+) to add mystring and mystring, or mystring and char* objects")
	{
		*msEmpty = *msArr + *msString;
		REQUIRE(strcmp(msEmpty->c_str(), ch) == 0); //mystring+mystring

		*msEmpty = "";
		*msEmpty = *msEmpty + *msEmpty;
		REQUIRE(msEmpty->length() == 0); //adding empty mystrings results in empty mystring

		*msEmpty = *msArr + ch2;
		REQUIRE(strcmp(msEmpty->c_str(), "abcabcz") == 0); //mystring+char*

		*msEmpty = "";
		*msEmpty = ch2 + *msArr;
		REQUIRE(strcmp(msEmpty->c_str(), "abczabc") == 0); //char*+mystring
	}

	SECTION("mystring objects can be used with IO operators")
	{
		std::stringstream s;
		*msEmpty = "";

		SECTION("mystring objects can be used with <<")
		{
			s.str("");
			s << *msEmpty;
			REQUIRE(s.str() == ""); //empty mystring

			s.str("");
			s << *msArr;
			REQUIRE(s.str() == "abc");

			SECTION("mystring object << operations can be chained")
			{
				s.str("");
				s << *msMs << *msString;
				REQUIRE(s.str() == "abcdefghi");
			}
		}

		SECTION("mystring objects can be used with >>")
		{
			s.str("");
			s << *msArr;
			s >> *msEmpty;
			REQUIRE(strcmp(msEmpty->c_str(), "abc") == 0);

		}
	}
}