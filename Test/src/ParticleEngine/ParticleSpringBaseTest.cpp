/* 
 * Created by Matthias "Nelaty" Gensheimer on 02.03.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "ThirdParty/catch.hpp"
#include "R3D/ParticleEngine/ParticleSpringBase.h"

class SpringTest : public r3::ParticleSpringBase
{
public:
    SpringTest(){}
    SpringTest(r3::real springConstant, r3::real restLength)
        : r3::ParticleSpringBase{springConstant, restLength}
    {}

    void updateForce(r3::Particle* particle) override {}
};

TEST_CASE("Setter getter tests")
{
    SpringTest spring;

    SECTION("rest length")
    {
        spring.setRestLength(0.5);
        CHECK(spring.getRestLength() == Approx(0.5));
        spring.setRestLength(0.0);
        CHECK(spring.getRestLength() == Approx(0.0));
        spring.setRestLength(-202.1);
        CHECK(spring.getRestLength() == Approx(-202.1));
    }
    SECTION("spring constant")
    {
        spring.setSpringConstant(4.1);
        CHECK(spring.getSpringConstant() == Approx(4.1));
        spring.setSpringConstant(0.0);
        CHECK(spring.getSpringConstant() == Approx(0.0));
        spring.setSpringConstant(-664.12);
        CHECK(spring.getSpringConstant() == Approx(-664.12));
    }
}

TEST_CASE("isMagnitudeValid")
{
    SpringTest spring;
    glm::vec3 distance;
    r3::real magnitude;
    SECTION("A distance of 0 is invalid")
    {
        CHECK_FALSE(spring.isMagnitudeValid(glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 0.0, 0.0),
                distance,
                magnitude));
        CHECK(distance == glm::vec3(0));
        CHECK(magnitude == 0);

        CHECK_FALSE(spring.isMagnitudeValid(glm::vec3(10.0, 4.1, -1.3),
                                            glm::vec3(10.0, 4.1, -1.3),
                                            distance,
                                            magnitude));
        CHECK(distance == glm::vec3(0));
        CHECK(magnitude == 0);
    }
    SECTION("Two points with a distance of 1 are valid")
    {
        CHECK(spring.isMagnitudeValid(glm::vec3(1.0, 2.0, -3.0),
                glm::vec3(2.0, 2.0, -3.0),
                distance,
                magnitude));
        CHECK(distance == glm::vec3(-1.0, 0.0, 0.0));
        CHECK(magnitude == Approx(1.0));
    }
    SECTION("Two points with a distance of 5 are valid")
    {
        CHECK(spring.isMagnitudeValid(glm::vec3(-1.0, 2.0, -3.0),
                                      glm::vec3(-1.0, 5.0, 1.0),
                                      distance,
                                      magnitude));
        CHECK(distance == glm::vec3(0.0, -3.0, -4.0));
        CHECK(magnitude == Approx(5.0));
    }
}
