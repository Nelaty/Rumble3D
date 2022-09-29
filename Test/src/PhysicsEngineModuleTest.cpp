/* 
 * Created by Matthias "Nelaty" Gensheimer on 26.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include "R3D/PhysicsEngineModule.h"
#include "R3D/IComputationInterface.h"

#include "catch2/catch_all.hpp"

class TestModule : public r3::PhysicsEngineModule
{
public:
    TestModule() : r3::PhysicsEngineModule("TestModule"){};
    r3::IComputationInterface* getComputationInterface() const override {return nullptr;}
};



TEST_CASE("Change the name of a module")
{
    TestModule module;
    CHECK(module.getName() == "TestModule");
    module.setName("RenamedModule");
    CHECK(module.getName() == "RenamedModule");
}

TEST_CASE("Enable and disable a module")
{
    TestModule module;
    CHECK(module.isEnabled());
    module.enable(false);
    CHECK_FALSE(module.isEnabled());
    module.enable(false);
    CHECK_FALSE(module.isEnabled());
    module.enable(true);
    CHECK(module.isEnabled());
}