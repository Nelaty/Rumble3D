/* 
 * Created by Matthias "Nelaty" Gensheimer on 24.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include <R3D/ParticleEngine/Particle.h>

#include <ThirdParty/catch.hpp>
#include <Test/vec_compare.h>

#include <stdexcept>
#include <climits>


TEST_CASE("Particle mass")
{
    r3::Particle particle;

    SECTION("Mass higher than 0 is allowed")
    {
        particle.setMass(1);
        CHECK(particle.getMass() == Approx(1));
        CHECK(particle.getInverseMass() == Approx(1));

        particle.setMass(50);
        CHECK(particle.getMass() == Approx(50));
        CHECK(particle.getInverseMass() == Approx(0.02));
    }
    SECTION("Mass <= 0 is forbidden")
    {
        particle.setMass(2);

        CHECK_THROWS_AS(particle.setMass(0), std::invalid_argument);
        CHECK(particle.getMass() == Approx(2));
        CHECK(particle.getInverseMass() == Approx(0.5));

        CHECK_THROWS_AS(particle.setMass(-1), std::invalid_argument);
        CHECK(particle.getMass() == Approx(2));
        CHECK(particle.getInverseMass() == Approx(0.5));
    }
    SECTION("Inverse mass must be positive or 0")
    {
        particle.setMass(10);

        CHECK_THROWS_AS(particle.setInverseMass(-0.0001), std::invalid_argument);
        CHECK(particle.getMass() == Approx(10));
        CHECK_THROWS_AS(particle.setInverseMass(-1), std::invalid_argument);
        CHECK(particle.getMass() == Approx(10));

        particle.setInverseMass(0);
        CHECK(particle.getInverseMass() == Approx(0));
        CHECK(particle.getMass() == Approx(std::numeric_limits<r3::real>::max()));
        particle.setInverseMass(0.5);
        CHECK(particle.getInverseMass() == Approx(0.5));
        CHECK(particle.getMass() == Approx(2.0));
        particle.setInverseMass(20);
        CHECK(particle.getInverseMass() == Approx(20));
        CHECK(particle.getMass() == Approx(0.05));
    }
    SECTION("An inverse mass of zero equals infinite mass")
    {
        particle.setInverseMass(0);
        CHECK_FALSE(particle.hasFiniteMass());
    }
    SECTION("A particle with inverse mass larger than 0 has finite mass")
    {
        particle.setInverseMass(0);
        CHECK_FALSE(particle.hasFiniteMass());

        particle.setInverseMass(0.0001);
        CHECK(particle.hasFiniteMass());
        particle.setMass(10);
        CHECK(particle.hasFiniteMass());
    }
    SECTION("Init a particle with a particle definition structure and reset it")
    {
        r3::ParticleDef def;
        def.setInfiniteMass();
        def.m_position = glm::vec3(0.4, 0.0, 41.1);
        def.m_velocity = glm::vec3(-2.0, 6.2, 0.0);
        def.m_acceleration = glm::vec3(0.0, -1.5, 5.9);
        def.m_damping = 0.078;
        def.m_isDead = false;
        def.m_forceAccumulator = glm::vec3(0.1, -2.2, 4.8);

        particle.init(def);

        CHECK(particle.getInverseMass() == def.m_inverseMass);
        CHECK(particle.getPosition() == def.m_position);
        CHECK(particle.getVelocity() == def.m_velocity);
        CHECK(particle.getAcceleration() == def.m_acceleration);
        CHECK(particle.getDamping() == def.m_damping);
        CHECK(particle.getForceAccumulator() == def.m_forceAccumulator);
        CHECK(particle.isDead() == def.m_isDead);

        particle.reset(glm::vec3(-1.1, 3.1, 10.0));
        CHECK(particle.getInverseMass() == def.m_inverseMass);
        CHECK(particle.getPosition() == glm::vec3(-1.1, 3.1, 10.0));
        CHECK(particle.getVelocity() == glm::vec3(0));
        CHECK(particle.getAcceleration() == glm::vec3(0));
        CHECK(particle.getDamping() == def.m_damping);
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
        CHECK_FALSE(particle.isDead());
    }
    SECTION("Position manipulation")
    {
        particle.setPosition(glm::vec3(0));
        CHECK(test::compareApprox(particle.getPosition(), glm::vec3(0)));
        particle.setPosition(glm::vec3(-1.0, 1.0, 4.4));
        CHECK(test::compareApprox(particle.getPosition(), glm::vec3(-1.0, 1.0, 4.4)));
    }
    SECTION("Velocity manipulation")
    {
        particle.setVelocity(glm::vec3(0));
        CHECK(test::compareApprox(particle.getVelocity(), glm::vec3(0)));
        particle.setVelocity(glm::vec3(2.2, -19.4, 12.0));
        CHECK(test::compareApprox(particle.getVelocity(), glm::vec3(2.2, -19.4, 12.0)));
    }
    SECTION("Acceleration manipulation")
    {
        particle.setAcceleration(glm::vec3(0));
        CHECK(test::compareApprox(particle.getAcceleration(), glm::vec3(0)));
        particle.setAcceleration(glm::vec3(44.1, 98.41, -22.22));
        CHECK(test::compareApprox(particle.getAcceleration(), glm::vec3(44.1, 98.41, -22.22)));
    }
    SECTION("Damping manipulation")
    {
        particle.setDamping(0.0);
        CHECK(particle.getDamping() == Approx(0.0));
        particle.setDamping(0.091);
        CHECK(particle.getDamping() == Approx(0.091));
        particle.setDamping(-1.41);
        CHECK(particle.getDamping() == Approx(-1.41));
    }
    SECTION("Change dead status")
    {
        particle.setIsDead(false);
        CHECK_FALSE(particle.isDead());
        particle.setIsDead(true);
        CHECK(particle.isDead());
    }
    SECTION("Force accumulator manipulation")
    {
        particle.clearAccumulator();
        CHECK(particle.getForceAccumulator() == glm::vec3(0));
        particle.addForce(glm::vec3(2.0));
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(2.0)));
        particle.addForce(glm::vec3(-3.0, 4.0, 5.0));
        CHECK(test::compareApprox(particle.getForceAccumulator(), glm::vec3(-1.0, 6.0, 7.0)));
    }
    SECTION("Test cases where integration doesn't change the state")
    {
        particle.setPosition(10.0, -5.0, 4.0);
        particle.setVelocity(glm::vec3(10.0, 1.0, -4.0));
        particle.setMass(1.0);

        SECTION("Dead particle")
        {
            particle.setIsDead(true);
            r3::Particle previousState = particle;
            particle.integrate(1.0);
            CHECK(particle == previousState);
        }
        SECTION("Infinite mass")
        {
            particle.setInverseMass(0);
            r3::Particle previousState = particle;
            particle.integrate(1.0);
            CHECK(particle == previousState);
        }
        SECTION("Zero time delta")
        {
            r3::Particle previousState = particle;
            particle.integrate(0.0);
            CHECK(particle == previousState);
        }
    }
    SECTION("integrator test")
    {
        glm::vec3 startingPos(10.0, -5.0, 4.0);
        glm::vec3 velocity(10.0, 1.0, -4.0);

        particle.setPosition(10.0, -5.0, 4.0);
        particle.setVelocity(glm::vec3(10.0, 1.0, -4.0));
        particle.setMass(1.0);
        particle.setDamping(1.0);

        SECTION("0.5s step")
        {
            particle.integrate(0.5);
            CHECK(test::compareApprox(particle.getPosition(),
                                      startingPos + r3::real(0.5) * velocity));
        }
        SECTION("2s step")
        {
            particle.integrate(2.0);
            test::compareApprox(particle.getPosition(),
                                startingPos + r3::real(2.0) * velocity);
        }
        SECTION("acceleration")
        {
            glm::vec3 acceleration(10.0, -1.0, 4.0);
            particle.setAcceleration(acceleration);
            particle.integrate(2.0);
            test::compareApprox(particle.getVelocity(),
                                velocity + r3::real(2) * acceleration);
        }
        SECTION("Damping slightly reduces velocity")
        {
            particle.integrate(1.0);

        }
    }
}