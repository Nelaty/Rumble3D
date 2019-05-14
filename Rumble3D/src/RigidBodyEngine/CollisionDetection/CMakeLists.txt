target_sources(rumble3D
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BroadPhaseFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CollisionAlgorithmMatrix.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CollisionData.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CollisionDetector.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CollisionMask.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CollisionPair.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Contact.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IBroadPhaseFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IIntermediatePhaseFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/INarrowPhaseAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/INarrowPhaseFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NarrowPhaseFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/OctreeBroadPhaseFilter.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Octree.cpp
)

add_subdirectory(Algorithm)
