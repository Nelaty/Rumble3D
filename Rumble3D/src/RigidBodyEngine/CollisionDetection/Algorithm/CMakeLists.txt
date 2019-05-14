target_sources(rumble3D
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BoxBoxNarrowAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/BoxSphereNarrowAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IBoxBoxNarrowAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IBoxSphereNarrowAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IPlaneBoxCollisionAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IPlanePlaneCollisionAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/IPlaneSphereCollisionAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ISphereSphereNarrowAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NullAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PlaneBoxCollisionAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PlanePlaneCollisionAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PlaneSphereCollisionAlgorithm.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SphereSphereNarrowAlgorithm.cpp
)
