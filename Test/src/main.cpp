#include "UnitTest++.h"
#include "R3D/PhysicsEngine.h"

TEST(mySuccessfulTest)
{
	rum::TestClass simpleTest;
	CHECK_EQUAL(3, simpleTest.test());
}

TEST(myUnsuccessfulTest)
{
	rum::TestClass simpleTest;
	CHECK_EQUAL(1, simpleTest.test());
}

int main(int argc, char** argv)
{
	UnitTest::RunAllTests();

	getchar();
} 