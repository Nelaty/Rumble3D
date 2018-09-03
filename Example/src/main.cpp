#include <iostream>
#include "R3D/PhysicsEngine.h"

int main(int argc, char** argv)
{
	r3::PhysicsEngine physicsEngine;
	physicsEngine.tick(1);

	getchar();
}