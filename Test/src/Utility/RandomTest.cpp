/* 
 * Created by Matthias "Nelaty" Gensheimer on 26.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "ThirdParty/catch.hpp"
#include "R3D/Utility/Random.h"
#include "Test/vec_compare.h"

#include <stdexcept>
#include <iostream>

TEST_CASE("Seeding")
{
    r3::Random::seed(1337);
    CHECK(r3::Random::getSeed() == 1337);
    r3::Random::seed(0);
    CHECK(r3::Random::getSeed() == 0);
}

TEST_CASE("Random integer")
{
    constexpr int initialSeed = 42;
    r3::Random::seed(initialSeed);
    SECTION("A one item range will always yield the same result")
    {
        CHECK(r3::Random::randomInt(0, 0) == 0);
        CHECK(r3::Random::randomInt(-1, -1) == -1);
        CHECK(r3::Random::randomInt(1, 1) == 1);
    }
    SECTION("The random element will always be in the specified range")
    {
        for(int i = 0; i < 10; ++i)
        {
            int result = r3::Random::randomInt(0, 10);
            std::array<int, 3> results;
            results[0] = r3::Random::randomInt(0,10);
            results[1] = r3::Random::randomInt(-6,0);
            results[2] = r3::Random::randomInt(-19,22);
            CHECK((results[0] >= 0 && results[0] <= 10));
            CHECK((results[1] >= -6 && results[1] <= 0));
            CHECK((results[2] >= -19 && results[2] <= 22));
        }
    }
    SECTION("A series of random numbers is always the same for a specific seed")
    {
        std::vector<int> nums;
        for(int i = 0; i < 10; ++i)
        {
            nums.emplace_back(r3::Random::randomInt());
        }

        r3::Random::seed(initialSeed);
        for(int i = 0; i < 10; ++i)
        {
            CHECK(nums[i] == r3::Random::randomInt());
        }
    }
    SECTION("The minimal value has to be less than the maximal")
    {
        CHECK_THROWS_AS(r3::Random::randomInt(0, -1), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomInt(100, 44), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomInt(14, -18), std::invalid_argument);
    }
}

TEST_CASE("Random float")
{
    constexpr int initialSeed = 1000;
    r3::Random::seed(initialSeed);
    SECTION("The result will always be the same if min == max")
    {
        CHECK(r3::Random::randomFloat(1.0, 1.0) == Approx(1.0));
        CHECK(r3::Random::randomFloat(0.0, 0.0) == Approx(0.0));
        CHECK(r3::Random::randomFloat(-3.3, -3.3) == Approx(-3.3));
    }
    SECTION("The random element will always be in the specified range")
    {
        for(int i = 0; i < 10; ++i)
        {
            std::array<float, 3> results;
            results[0] = r3::Random::randomFloat(0.0, 10.0);
            results[1] = r3::Random::randomFloat(-14.4, 0.0);
            results[2] = r3::Random::randomFloat(-1.5, 12.4);

            CHECK((results[0] >= Approx(0.0) && results[0] <= Approx(10.0)));
            CHECK((results[1] >= Approx(-14.4) && results[1] <= Approx(0.0)));
            CHECK((results[2] >= Approx(-1.5) && results[2] <= Approx(12.4)));
        }
    }
    SECTION("A series of random numbers is always the same for a specific seed")
    {
        std::vector<float> series;
        for(int i = 0; i < 10; ++i)
        {
            series.emplace_back(r3::Random::randomFloat());
        }

        r3::Random::seed(initialSeed);
        for(const auto& it : series)
        {
            CHECK(it == Approx(r3::Random::randomFloat()));
        }
    }
    SECTION("ZeroOne results lie in [0, 1]")
    {
        for(int i = 0; i < 10; ++i)
        {
            float result = r3::Random::randomFloatZeroOne();
            CHECK((result >= Approx(0) && result <= Approx(1)));
        }
    }
    SECTION("The minimal value has to be less than the maximal")
    {
        CHECK_THROWS_AS(r3::Random::randomFloat(0.0, -1.0), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomFloat(10.4, 4.4), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomFloat(-33.0, -33.1), std::invalid_argument);
    }
}

TEST_CASE("Random double")
{
    constexpr int initialSeed = 2000;
    r3::Random::seed(initialSeed);
    SECTION("The result will always be the same if min == max")
    {
        CHECK(r3::Random::randomDouble(1.0, 1.0) == Approx(1.0));
        CHECK(r3::Random::randomDouble(0.0, 0.0) == Approx(0.0));
        CHECK(r3::Random::randomDouble(-3.3, -3.3) == Approx(-3.3));
    }
    SECTION("The random element will always be in the specified range")
    {
        for(int i = 0; i < 10; ++i)
        {
            std::array<double , 3> results;
            results[0] = r3::Random::randomDouble(0.0, 10.0);
            results[1] = r3::Random::randomDouble(-14.4, 0.0);
            results[2] = r3::Random::randomDouble(-1.5, 12.4);

            CHECK((results[0] >= Approx(0.0) && results[0] <= Approx(10.0)));
            CHECK((results[1] >= Approx(-14.4) && results[1] <= Approx(0.0)));
            CHECK((results[2] >= Approx(-1.5) && results[2] <= Approx(12.4)));
        }
    }
    SECTION("A series of random numbers is always the same for a specific seed")
    {
        std::vector<double> series;
        for(int i = 0; i < 10; ++i)
        {
            series.emplace_back(r3::Random::randomDouble());
        }

        r3::Random::seed(initialSeed);
        for(const auto& it : series)
        {
            CHECK(it == Approx(r3::Random::randomDouble()));
        }
    }
    SECTION("ZeroOne results lie in [0, 1]")
    {
        for(int i = 0; i < 10; ++i)
        {
            double result = r3::Random::randomDoubleZeroOne();
            CHECK((result >= Approx(0) && result <= Approx(1)));
        }
    }
    SECTION("The minimal value has to be less than the maximal")
    {
        CHECK_THROWS_AS(r3::Random::randomDouble(0.0, -3.3), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomDouble(-51.0, -51.3), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomDouble(12.0, 5.5), std::invalid_argument);
    }
}
#include <iostream>
TEST_CASE("Random bool distribution")
{
    constexpr int initialSeed = 3000;
    r3::Random::seed(initialSeed);

    std::array<int, 2> distribution{};
    for (int i = 0; i < 100; ++i)
    {
        int num = r3::Random::randomBool(0.25);
        distribution[int(num)]++;
    }
    CHECK(distribution[0] >= distribution[1]);
}

TEST_CASE("Random sign")
{
    constexpr int initialSeed = 4000;
    r3::Random::seed(initialSeed);

    SECTION("The result is either +1 oder -1")
    {
        for(int i = 0; i < 10; ++i)
        {
            int result = r3::Random::randomSign(0.5);
            CHECK((result == -1 || result == 1));
        }
    }
    SECTION("Sign distribution is statistically correct")
    {
        std::array<int, 2> distribution{};
        for (int i = 0; i < 100; ++i)
        {
            int sign = r3::Random::randomSign(0.25);
            distribution[(sign + 1) / 2]++;
        }
        CHECK(distribution[0] >= distribution[1]);
    }
}

TEST_CASE("Random 2d vector")
{
    constexpr int initialSeed = 5000;
    r3::Random::seed(initialSeed);

    SECTION("A series of random vectors repeats itself for the same seed")
    {
        std::array<glm::vec2, 2> results;
        results[0] = r3::Random::randomVec2();
        results[1] = r3::Random::randomVec2();

        CHECK(results[0] != results[1]);
        r3::Random::seed(initialSeed);
        CHECK(results[0] == r3::Random::randomVec2());
        CHECK(results[1] == r3::Random::randomVec2());
    }
    SECTION("Random vector with same range for all components")
    {
        std::array<glm::vec2, 3> results;
        results[0] = r3::Random::randomVec2(0.0, 1.0);
        results[1] = r3::Random::randomVec2(-4.0, 0.0);
        results[2] = r3::Random::randomVec2(-8.8, 4.1);

        CHECK((results[0].x >= Approx(0.0) && results[0].x <= Approx(1.0)));
        CHECK((results[0].y >= Approx(0.0) && results[0].y <= Approx(1.0)));

        CHECK((results[1].x >= Approx(-4.0) && results[1].x <= Approx(0.0)));
        CHECK((results[1].y >= Approx(-4.0) && results[1].y <= Approx(0.0)));

        CHECK((results[2].x >= Approx(-8.8) && results[2].x <= Approx(4.1)));
        CHECK((results[2].y >= Approx(-8.8) && results[2].y <= Approx(4.1)));
    }
    SECTION("Random vector with individual range for each component")
    {
        std::array<glm::vec2, 3> results;
        results[0] = r3::Random::randomVec2(glm::vec2(0.0), glm::vec2(0.0));
        results[1] = r3::Random::randomVec2(glm::vec2(-2.0, 5.0), glm::vec2(-2.0, 5.0));
        results[2] = r3::Random::randomVec2(glm::vec2(-1.4, -8.3), glm::vec2(4.2, 6.7));

        CHECK(results[0] == glm::vec2(0));
        CHECK(results[1] == glm::vec2(-2.0, 5.0));
        CHECK((results[2].x >= Approx(-1.4)
            && results[2].x <= Approx(4.2)
            && results[2].y >= Approx(-8.3)
            && results[2].y <= Approx(6.7)));
    }
    SECTION("The range for each component has to be well defined (min >= max)")
    {
        CHECK_THROWS_AS(r3::Random::randomVec2(glm::vec2(0), glm::vec2(-0.001)), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec2(glm::vec2(0), glm::vec2(-0.001, 0.0)), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec2(glm::vec2(0), glm::vec2(0.0, -0.001)), std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec2(glm::vec2(-5.4, 9.2), glm::vec2(-8.0, 6.2)), std::invalid_argument);
    }
}

TEST_CASE("Random 3d vector")
{
    constexpr int initialSeed = 6000;
    r3::Random::seed(initialSeed);

    SECTION("A series of random vectors repeats itself for the same seed")
    {
        std::array<glm::vec3, 2> results;
        results[0] = r3::Random::randomVec3();
        results[1] = r3::Random::randomVec3();

        CHECK(results[0] != results[1]);
        r3::Random::seed(initialSeed);
        CHECK(results[0] == r3::Random::randomVec3());
        CHECK(results[1] == r3::Random::randomVec3());
    }
    SECTION("Random vector with same range for all components")
    {
        std::array<glm::vec3, 3> results;
        results[0] = r3::Random::randomVec3(0.0, 4.0);
        results[1] = r3::Random::randomVec3(-8.8, 0.0);
        results[2] = r3::Random::randomVec3(-2.4, 12.4);

        CHECK((results[0].x >= Approx(0.0) && results[0].x <= Approx(4.0)));
        CHECK((results[0].y >= Approx(0.0) && results[0].y <= Approx(4.0)));
        CHECK((results[0].z >= Approx(0.0) && results[0].z <= Approx(4.0)));

        CHECK((results[1].x >= Approx(-8.8) && results[1].x <= Approx(0.0)));
        CHECK((results[1].y >= Approx(-8.8) && results[1].y <= Approx(0.0)));
        CHECK((results[1].z >= Approx(-8.8) && results[1].z <= Approx(0.0)));

        CHECK((results[2].x >= Approx(-2.4) && results[2].x <= Approx(12.4)));
        CHECK((results[2].y >= Approx(-2.4) && results[2].y <= Approx(12.4)));
        CHECK((results[2].z >= Approx(-2.4) && results[2].z <= Approx(12.4)));
    }
    SECTION("Random vector with individual range for each component")
    {
        std::array<glm::vec3, 3> results;
        results[0] = r3::Random::randomVec3(glm::vec3(0),
                                            glm::vec3(0));
        results[1] = r3::Random::randomVec3(glm::vec3(-12.0, 23.0, 14.2),
                                            glm::vec3(-12.0, 23.0, 14.2));
        results[2] = r3::Random::randomVec3(glm::vec3(8.0, -6.2, 8.8),
                                            glm::vec3(30.0, -4.0, 33.3));

        CHECK(results[0] == glm::vec3(0));
        CHECK(results[1] == glm::vec3(-12.0, 23.0, 14.2));
        CHECK((results[2].x >= Approx(8.0) && results[2].x <= Approx(30.0)));
        CHECK((results[2].y >= Approx(-6.2) && results[2].y <= Approx(-4.0)));
        CHECK((results[2].z >= Approx(8.8) && results[2].z <= Approx(33.3)));
    }
    SECTION("The range for each component has to be well defined (min >= max)")
    {
        CHECK_THROWS_AS(r3::Random::randomVec3(glm::vec3(0),
                                               glm::vec3(-0.001)),
                       std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec3(glm::vec3(0),
                                               glm::vec3(-0.001, 0.0, 0.0)),
                       std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec3(glm::vec3(0),
                                               glm::vec3(0.0, -0.001, 0.0)),
                       std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec3(glm::vec3(0),
                                               glm::vec3(0.0, 0.0, -0.001)),
                       std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec3(glm::vec3(4.2, -6.0, -12.6),
                                               glm::vec3(2.0, -8.0, -15.0)),
                       std::invalid_argument);
    }
}

TEST_CASE("Random 4d vector")
{
    constexpr int initialSeed = 7000;
    r3::Random::seed(initialSeed);

    SECTION("A series of random vectors repeats itself for the same seed")
    {
        std::array<glm::vec4, 2> results;
        results[0] = r3::Random::randomVec4();
        results[1] = r3::Random::randomVec4();

        CHECK(results[0] != results[1]);
        r3::Random::seed(initialSeed);
        CHECK(results[0] == r3::Random::randomVec4());
        CHECK(results[1] == r3::Random::randomVec4());
    }
    SECTION("Random vector with same range for all components")
    {
        std::array<glm::vec4, 3> results;
        results[0] = r3::Random::randomVec4(0.0, 4.4);
        results[1] = r3::Random::randomVec4(-9.0, 0.0);
        results[2] = r3::Random::randomVec4(-4.0, 7.5);

        CHECK((results[0].x >= Approx(0.0) && results[0].x <= Approx(4.4)));
        CHECK((results[0].y >= Approx(0.0) && results[0].y <= Approx(4.4)));
        CHECK((results[0].z >= Approx(0.0) && results[0].z <= Approx(4.4)));
        CHECK((results[0].w >= Approx(0.0) && results[0].w <= Approx(4.4)));

        CHECK((results[1].x >= Approx(-9.0) && results[1].x <= Approx(0.0)));
        CHECK((results[1].y >= Approx(-9.0) && results[1].y <= Approx(0.0)));
        CHECK((results[1].z >= Approx(-9.0) && results[1].z <= Approx(0.0)));
        CHECK((results[1].w >= Approx(-9.0) && results[1].w <= Approx(0.0)));

        CHECK((results[2].x >= Approx(-4.0) && results[2].x <= Approx(7.5)));
        CHECK((results[2].y >= Approx(-4.0) && results[2].y <= Approx(7.5)));
        CHECK((results[2].z >= Approx(-4.0) && results[2].z <= Approx(7.5)));
        CHECK((results[2].w >= Approx(-4.0) && results[2].w <= Approx(7.5)));
    }
    SECTION("Random vector with individual range for each component")
    {
        std::array<glm::vec4, 3> results;
        results[0] = r3::Random::randomVec4(glm::vec4(0),
                                            glm::vec4(0));
        results[1] = r3::Random::randomVec4(glm::vec4(-2.2, 22.4, -122.3, 1.1),
                                            glm::vec4(-2.2, 22.4, -122.3, 1.1));
        results[2] = r3::Random::randomVec4(glm::vec4(-4.0, -1.0, 2.5, 66.0),
                                            glm::vec4(-2.5, 20.1, 14.2, 112.2));

        CHECK(results[0] == glm::vec4(0));
        CHECK(results[1] == glm::vec4(-2.2, 22.4, -122.3, 1.1));
        CHECK((results[2].x >= Approx(-4.0) && results[2].x <= Approx(-2.5)));
        CHECK((results[2].y >= Approx(-1.0) && results[2].y <= Approx(20.1)));
        CHECK((results[2].z >= Approx(2.5) && results[2].z <= Approx(14.2)));
        CHECK((results[2].w >= Approx(66.6) && results[2].w <= Approx(112.2)));

    }
    SECTION("The range for each component has to be well defined (min >= max)")
    {
        CHECK_THROWS_AS(r3::Random::randomVec4(glm::vec4(0),
                                               glm::vec4(-0.001)),
                        std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec4(glm::vec4(0),
                                               glm::vec4(-0.001, 0.0, 0.0, 0.0)),
                        std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec4(glm::vec4(0),
                                               glm::vec4(0.0, -0.001, 0.0, 0.0)),
                        std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec4(glm::vec4(0),
                                               glm::vec4(0.0, 0.0, -0.001, 0.0)),
                        std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec4(glm::vec4(0),
                                               glm::vec4(0.0, 0.0, 0.0, -0.001)),
                        std::invalid_argument);
        CHECK_THROWS_AS(r3::Random::randomVec4(glm::vec4(4.2, -6.0, -12.6, 52.3),
                                               glm::vec4(2.0, -8.0, -15.0, 14.5)),
                        std::invalid_argument);
    }
    r3::Random::seed(0);
}