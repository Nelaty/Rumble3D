#include "R3D/PhysicsEngine.h"
#include "R3D/ParticleEngine/Particle.h"

#include "glm/glm.hpp"

#include <stdio.h>

int main(int argc, char** argv)
{
	r3::PhysicsEngine physicsEngine;
	physicsEngine.tick(1);

	r3::Particle particle;
	particle.addForce(glm::vec3(10.0f));

	getchar();
}