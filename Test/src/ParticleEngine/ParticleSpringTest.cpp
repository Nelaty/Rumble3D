/* 
 * Created by Matthias "Nelaty" Gensheimer on 02.03.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "catch2/catch_all.hpp"
#include "R3D/ParticleEngine/ParticleSpring.h"
#include "R3D/ParticleEngine/Particle.h"

#include "Test/vec_compare.h"

#include <glm/gtx/io.hpp>
#include <iostream>

using namespace Catch;

TEST_CASE("Test constructor")
{
    r3::Particle particle;
    SECTION("Pass nullptr as particle")
    {
        r3::ParticleSpring spring(nullptr, 0.2, 10.0);
        CHECK(spring.getOther() == nullptr);
        CHECK(spring.getRestLength() == Approx(10.0));
        CHECK(spring.getSpringConstant() == Approx(0.2));
    }
    SECTION("Pass valid particle")
    {
        r3::ParticleSpring spring(&particle, 0.2, 10.0);
        CHECK(spring.getOther() == &particle);
    }
    SECTION("Default constructor should zero initialize")
    {
        r3::ParticleSpring spring;
        CHECK(spring.getOther() == nullptr);
        CHECK(spring.getSpringConstant() == 0);
        CHECK(spring.getRestLength() == 0);
    }
}

TEST_CASE("Getter and setter")
{
    r3::ParticleSpring spring;
    r3::Particle particle;

    SECTION("Get and set other")
    {
        spring.setOther(&particle);
        CHECK(spring.getOther() == &particle);
    }
    SECTION("Get and set other nullptr")
    {
        spring.setOther(nullptr);
        CHECK(spring.getOther() == nullptr);
    }
}

TEST_CASE("Force calculation")
{
    r3::Particle particle;
    r3::Particle other;
    r3::ParticleSpring spring(&other, 0.0, 0.0);


    SECTION("Zero distance has no effect")
    {
        spring.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
        CHECK(other.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("No force is applied when the distance equals the rest distance")
    {
        particle.setPosition(1.0, 0.0, 0.0);
        spring.setRestLength(1.0);
        spring.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
        CHECK(other.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("No force is applied when the spring constant is zero")
    {
        particle.setPosition(0.0, 1.0, 0.0);
        spring.setRestLength(2.0);
        spring.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
        CHECK(other.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("A larger distance than the rest length creates attractive forces")
    {
        particle.setPosition(0.0, 2.0, 0.0);
        spring.setRestLength(1.0);
        spring.setSpringConstant(1.0);
        spring.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(0, -1, 0));
        CHECK(other.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("A smaller distance than the rest length creates repulsive forces")
    {
        particle.setPosition(1.0, 0.0, 0.0);
        spring.setRestLength(3.0);
        spring.setSpringConstant(1.0);
        spring.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(2, 0, 0));
        CHECK(other.getForceAccumulator() == glm::vec3(0));
    }
    SECTION("Check repulsion which affects all axis")
    {
        particle.setPosition(1.0, 1.0, 1.0);
        spring.setRestLength(2.0);
        spring.setSpringConstant(1.0);
        spring.updateForce(&particle);
        r3::real sqrt3 = sqrt(r3::real(3));
        r3::real force{(r3::real(2) - sqrt3)/sqrt3};
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(force, force, force)));
        CHECK(other.getForceAccumulator() == glm::vec3(0));
    }
}