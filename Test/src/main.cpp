#include "UnitTest++/UnitTest++.h"
#include "R3D/PhysicsEngine.h"
#include "../../../EyeCandy3D/External/unittest-cpp-master/UnitTest++/TestRunner.h"

TEST(mySuccessfulTest)
{
	r3::TestClass simpleTest;
	CHECK_EQUAL(3, simpleTest.test());
}

TEST(myUnsuccessfulTest)
{
	r3::TestClass simpleTest;
	CHECK_EQUAL(1, simpleTest.test());
}

int main(int argc, char** argv)
{
	UnitTest::RunAllTests();

	getchar();
} 