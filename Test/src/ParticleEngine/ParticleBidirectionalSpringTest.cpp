/* 
 * Created by Matthias "Nelaty" Gensheimer on 03.03.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "R3D/ParticleEngine/ParticleBidirectionalSpring.h"
#include "R3D/ParticleEngine/Particle.h"
#include "Test/vec_compare.h"
#include "ThirdParty/catch.hpp"

TEST_CASE("BidirectionalSpring Getter and setter")
{
    r3::ParticleBidirectionalSpring spring;
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

TEST_CASE("BidirectionalSpring force calculation")
{
    r3::Particle particle;
    r3::Particle other;
    r3::ParticleBidirectionalSpring spring(&other, 0.0, 0.0);

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
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(0, -0.5, 0)));
        CHECK(test::compareApprox(other.getForceAccumulator(), glm::vec3(0, 0.5, 0)));
    }
    SECTION("A smaller distance than the rest length creates repulsive forces")
    {
        particle.setPosition(1.0, 0.0, 0.0);
        spring.setRestLength(3.0);
        spring.setSpringConstant(1.0);
        spring.updateForce(&particle);
        CHECK(particle.getForceAccumulator() == glm::vec3(1, 0, 0));
        CHECK(other.getForceAccumulator() == glm::vec3(-1, 0, 0));
    }
}