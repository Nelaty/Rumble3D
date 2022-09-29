add_executable(${PROJECT_NAME}_unittests 
    src/ParticleEngine/ParticleBidirectionalSpringTest.cpp
    src/ParticleEngine/ParticleGravityTest.cpp
    src/ParticleEngine/ParticleSpringBaseTest.cpp
    src/ParticleEngine/ParticleSpringTest.cpp
    src/ParticleEngine/ParticleTest.cpp
    
    src/Test/vec_compare.cpp

    src/Utility/FixedSizeContainerTest.cpp
    src/Utility/RandomTest.cpp
    
    src/main.cpp
    src/PhysicsEngineModuleTest.cpp
    src/PhysicsEngineTest.cpp
    src/TransformTest.cpp
)
target_link_libraries(${PROJECT_NAME}_unittests  
        ${PROJECT_NAME}
        Catch2
        
)
target_include_directories(${PROJECT_NAME}_unittests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME ${PROJECT_NAME}_unittests COMMAND ${PROJECT_NAME}_unittests)
add_dependencies(ctest ${PROJECT_NAME}_unittests)
