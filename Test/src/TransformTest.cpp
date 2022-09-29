/*
 * Created by Matthias "Nelaty" Gensheimer on 26.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "R3D/Transform3D.h"

#include "Test/vec_compare.h"

#include "catch2/catch_all.hpp"

TEST_CASE("A new transformation is located in the origin and not rotated")
{
    r3::Transform3D transform;
    CHECK(transform.getPosition() == glm::vec3(0));
    CHECK(transform.getRotationMat() == glm::mat3(1));
}

TEST_CASE("Change the position")
{
    r3::Transform3D transform;
    transform.setPosition(10.0, -4.4, 3.3);
    CHECK(transform.getPosition() == glm::vec3(10.0, -4.4, 3.3));
    transform.setPosition(-2.2, 44.1, 0.0);
    CHECK(transform.getPosition() == glm::vec3(-2.2, 44.1, 0.0));
}

TEST_CASE("Translate")
{
    r3::Transform3D transform;
    transform.translate(44.0, 22.5, -11.0);
    CHECK(transform.getPosition() == glm::vec3(44.0, 22.5, -11.0));
    transform.translate(-44.0, 22.0, 4.0);
    CHECK(test::compareApprox(transform.getPosition(), glm::vec3(0.0, 44.5, -7.0)));
}

TEST_CASE("Rotate")
{
    // \todo
}

TEST_CASE("Translate, rotate and scale")
{
    // \todo
}

TEST_CASE("Transform between local and global coordinates")
{
    // \todo
}