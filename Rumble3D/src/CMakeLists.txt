add_library(rumble3D STATIC
	IComputationInterface.cpp
	PhysicsEngine.cpp
	PhysicsEngineModule.cpp
	Transform3D.cpp
)


target_include_directories(rumble3D PUBLIC ${PROJECT_SOURCE_DIR}/Rumble3D/include)

add_subdirectory(ParticleEngine)
add_subdirectory(RigidBodyEngine)
add_subdirectory(ServiceLocator)
add_subdirectory(Utility)

