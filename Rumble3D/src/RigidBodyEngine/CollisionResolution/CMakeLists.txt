target_sources(rumble3D
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CollisionResolver.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/FrictionResolver.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ICollisionResolutionFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ICollisionResolverAccess.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/InterpenetrationResolver.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/VelocityResolver.cpp
)
