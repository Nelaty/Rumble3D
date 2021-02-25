/* 
 * Created by Matthias "Nelaty" Gensheimer on 25.02.21.
 * Copyright (c) 2021 Matthias Gensheimer. All rights reserved.
 */

#include <R3D/PhysicsEngine.h>
#include <R3D/ParticleEngine/ParticleWorld.h>
#include <R3D/RigidBodyEngine/RigidBodyWorld.h>

#include <ThirdParty/catch.hpp>


TEST_CASE("Pause and resume")
{
    r3::PhysicsEngine engine;
    CHECK_FALSE(engine.isPaused());
    engine.pause();
    CHECK(engine.isPaused());
    engine.pause();
    CHECK(engine.isPaused());
    engine.resume();
    CHECK_FALSE(engine.isPaused());
    engine.resume();
    CHECK_FALSE(engine.isPaused());
}

TEST_CASE("Module Registration")
{
    r3::PhysicsEngine engine;

    SECTION("A new physics engine has no modules")
    {
        auto& modules = engine.getModules();
        CHECK(modules.size() == 0);
    }
    SECTION("Register and unregister modules")
    {
        auto particleWorld = std::make_shared<r3::ParticleWorld>();
        particleWorld->setName("particle");
        auto rigidBodyWorld = std::make_shared<r3::RigidBodyWorld>();
        rigidBodyWorld->setName("rigidBody");

        engine.registerModule(particleWorld);
        engine.registerModule(rigidBodyWorld);
        SECTION("Module registration status")
        {
            CHECK(engine.getModules().size() == 2);
            CHECK(engine.isModuleRegistered(particleWorld));
            CHECK(engine.isModuleRegistered(particleWorld.get()));
            CHECK(engine.isModuleRegistered("particle"));

            CHECK(engine.isModuleRegistered(rigidBodyWorld));
            CHECK(engine.isModuleRegistered(rigidBodyWorld.get()));
            CHECK(engine.isModuleRegistered("rigidBody"));
        }
        SECTION("Unregister modules by reference")
        {
            engine.unregisterModule(particleWorld);
            CHECK_FALSE(engine.isModuleRegistered(particleWorld));
            CHECK(engine.isModuleRegistered(rigidBodyWorld));
            CHECK(engine.getModules().size() == 1);

            engine.unregisterModule(rigidBodyWorld);
            CHECK_FALSE(engine.isModuleRegistered(rigidBodyWorld));
            CHECK(engine.getModules().size() == 0);
        }
        SECTION("Unregister modules by name")
        {
            engine.unregisterModule("particle");
            CHECK_FALSE(engine.isModuleRegistered(particleWorld));
            CHECK(engine.isModuleRegistered(rigidBodyWorld));
            CHECK(engine.getModules().size() == 1);

            engine.unregisterModule("rigidBody");
            CHECK_FALSE(engine.isModuleRegistered(rigidBodyWorld));
            CHECK(engine.getModules().size() == 0);
        }
    }
}