/**@file vector_vector_test.cpp
 * @brief unit testing using the Catch2 framework for the Vector<T> project.
 *
 *
 * @author Chen Kasirer
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "vector.hpp"
#include "sstream"

TEST_CASE("Assignment8 - vector - template implementation")
{
	Vector<int> *v1 = new Vector<int>();
	Vector<int> *v2 = new Vector<int>(3,2);
	Vector<double> *v3 = new Vector<double>(4, 2.33);

	Vector<Vector<int>> *v4 = new Vector<Vector<int>>(2,*v2);

	Vector<int> * v5 = new Vector<int>(4,9);
	
	SECTION("Test #1")
	{
		REQUIRE((*v1).to_string() == "()");
		REQUIRE((*v2).to_string() == "(2,2,2)");
		REQUIRE((*v3).to_string() == "(2.33,2.33,2.33,2.33)");
		REQUIRE((*v4).to_string() == "((2,2,2),(2,2,2))");
		REQUIRE(v5->to_string() == "(9,9,9,9)");
	}

	SECTION("Insert") 
	{
		v1->insert(0, 5);
		REQUIRE(v1->to_string() == "(5)");
		
		v1->insert(0, 5);
		REQUIRE(v1->to_string() == "(5,5)");
		
		v1->insert(0, *v2);
		REQUIRE(v1->to_string() == "(2,2,2,5,5)");

		v1->insert(3, *v5);
		REQUIRE(v1->to_string() == "(2,2,2,9,9,9,9,5,5)");
	}

	SECTION("Swap")
	{
		swap(*v2, *v5);
		REQUIRE(v2->size() == 4);
		REQUIRE(v2->to_string() == "(9,9,9,9)");
		REQUIRE(v5->size() == 3);
		REQUIRE(v5->to_string() == "(2,2,2)");
	}

	SECTION("Remove")
	{
		v2->remove(1);
		REQUIRE(v2->to_string() == "(2,2)");
		v2->remove(0);
		REQUIRE(v2->to_string() == "(2)");
		v2->remove(0);
		REQUIRE(v2->to_string() == "()");
	}
}
