#include <iostream>
#include "R3D/PhysicsEngine.h"

int main(int argc, char** argv)
{
	rum::PhysicsEngine physicsEngine;
	physicsEngine.update(1);

	getchar();
}