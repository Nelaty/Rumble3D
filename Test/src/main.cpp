#include "catch2/catch.hpp
#include "R3D/PhysicsEngine.h"

#include <stdio.h>

TEST(mySuccessfulTest)
{
	CHECK_EQUAL(3, 3);
}

TEST(myUnsuccessfulTest)
{
	CHECK_EQUAL(1, 3);
}

int main(int argc, char** argv)
{
	UnitTest::RunAllTests();
} 