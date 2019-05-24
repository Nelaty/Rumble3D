add_library(${PROJECT_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/IComputationInterface.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/PhysicsEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/PhysicsEngineModule.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Transform3D.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/Rumble3D/include)

add_subdirectory(src/ParticleEngine)
add_subdirectory(src/RigidBodyEngine)
add_subdirectory(src/ServiceLocator)
add_subdirectory(src/Utility)

