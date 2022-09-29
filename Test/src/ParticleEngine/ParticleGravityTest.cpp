/* 
 * Created by Matthias "Nelaty" Gensheimer on 28.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "catch2/catch_all.hpp"
#include "R3D/ParticleEngine/ParticleGravity.h"
#include "R3D/ParticleEngine/Particle.h"

#include "Test/vec_compare.h"

#include <iostream>

TEST_CASE("Test initialization")
{
    SECTION("Construct uniform")
    {
        r3::ParticleGravity gravity(24.0);
        CHECK(gravity.getGravity() == glm::vec3(24.0));
    }
    SECTION("Construct individual components")
    {
        r3::ParticleGravity gravity(-12.4, -4.1, 23.0);
        CHECK(gravity.getGravity() == glm::vec3(-12.4, -4.1, 23.0));
    }
    SECTION("Construct with vector")
    {
        r3::ParticleGravity gravity(glm::vec3(44.2, 11.5, 0.0));
        CHECK(gravity.getGravity() == glm::vec3(44.2, 11.5, 0.0));
    }
    SECTION("Change gravity after initialization")
    {
        r3::ParticleGravity gravity(14.4, 22.1, -22.1);
        gravity.setGravity(11.0, -92.1, 0.0);
        CHECK(gravity.getGravity() == glm::vec3(11.0, -92.1, 0.0));
    }
    SECTION("Change gravity after initialization")
    {
        r3::ParticleGravity gravity(0.0, 13.2, -22.1);
        gravity.setGravity(glm::vec3(41.2, 0.0, -56.1));
        CHECK(gravity.getGravity() == glm::vec3(41.2, 0.0, -56.1));
    }
    SECTION("Change gravity after initialization")
    {
        r3::ParticleGravity gravity(5.1, 22.1, 0.4);
        gravity.setGravity(8.4);
        CHECK(gravity.getGravity() == glm::vec3(8.4));
    }
}

TEST_CASE("Test applied force to particle")
{
    r3::ParticleGravity gravity;
    r3::Particle particle;
    particle.setMass(1.0);

    SECTION("Apply zero gravity")
    {
        gravity.setGravity(0.0);
        gravity.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("Apply gravity for 0 seconds")
    {
        gravity.setGravity(glm::vec3(0.0));
        gravity.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("Apply gravity in x axis direction")
    {
        gravity.setGravity(4.0, 0.0, 0.0);
        gravity.updateForce(&particle);
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(4.0, 0.0, 0.0)));
    }
    SECTION("Apply gravity in y axis direction")
    {
        gravity.setGravity(glm::vec3(0.0, 9.1, 0.0));
        gravity.updateForce(&particle);
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(0.0, 9.1, 0.0)));
    }
    SECTION("Apply gravity in z axis direction")
    {
        gravity.setGravity(0.0, 0.0, 8.2);
        gravity.updateForce(&particle);
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(0.0, 0.0, 8.2)));
    }
    SECTION("Apply gravity in all directions")
    {
        gravity.setGravity(-14.4, 4.0, 9.0);
        gravity.updateForce(&particle);
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(-14.4, 4.0, 9.0)));
    }
}