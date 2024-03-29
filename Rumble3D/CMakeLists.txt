# Set source files
if(RUMBLE3D_USE_DOUBLE_PRECISION)
    message("Double precision not supported yet. Fallback to 32 bit float.")
    set(R3D_CONFIG_USE_DOUBLE_PRECISION "0")
else()
    set(R3D_CONFIG_USE_DOUBLE_PRECISION "0")
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/R3D/Common/Config.h.in"
               "${CMAKE_CURRENT_SOURCE_DIR}/include/R3D/Common/Config.h"
               @ONLY)

add_library(${PROJECT_NAME}
        src/ParticleEngine/DefaultParticleEngineCI.cpp
        src/ParticleEngine/Particle.cpp
        src/ParticleEngine/ParticleAnchoredSpring.cpp
        src/ParticleEngine/ParticleBidirectionalSpring.cpp
        src/ParticleEngine/ParticleBungee.cpp
        src/ParticleEngine/ParticleBuoyancy.cpp
        src/ParticleEngine/ParticleCable.cpp
        src/ParticleEngine/ParticleCollision.cpp
        src/ParticleEngine/ParticleConstraint.cpp
        src/ParticleEngine/ParticleContact.cpp
        src/ParticleEngine/ParticleContactGeneratorRegistry.cpp
        src/ParticleEngine/ParticleContactResolver.cpp
        src/ParticleEngine/ParticleDef.cpp
        src/ParticleEngine/ParticleDrag.cpp
        src/ParticleEngine/ParticleEngineCI.cpp
        src/ParticleEngine/ParticleForceRegistry.cpp
        src/ParticleEngine/ParticleGravity.cpp
        src/ParticleEngine/ParticleLink.cpp
        src/ParticleEngine/ParticlePlaneContactGenerator.cpp
        src/ParticleEngine/ParticleRod.cpp
        src/ParticleEngine/ParticleSpring.cpp
        src/ParticleEngine/ParticleSpringBase.cpp
        src/ParticleEngine/ParticleWorld.cpp
        
        src/RigidBodyEngine/CollisionDetection/Algorithm/BoxBoxNarrowAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/BoxSphereNarrowAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/IBoxBoxNarrowAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/IBoxSphereNarrowAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/IPlaneBoxCollisionAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/IPlanePlaneCollisionAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/IPlaneSphereCollisionAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/ISphereSphereNarrowAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/NullAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/PlaneBoxCollisionAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/PlanePlaneCollisionAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/PlaneSphereCollisionAlgorithm.cpp
        src/RigidBodyEngine/CollisionDetection/Algorithm/SphereSphereNarrowAlgorithm.cpp

        src/RigidBodyEngine/CollisionDetection/BroadPhaseFilter.cpp
        src/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrix.cpp
        src/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrixFactory.cpp
        src/RigidBodyEngine/CollisionDetection/CollisionDetector.cpp
        src/RigidBodyEngine/CollisionDetection/CollisionMask.cpp
        src/RigidBodyEngine/CollisionDetection/CollisionPair.cpp
        src/RigidBodyEngine/CollisionDetection/Contact.cpp
        src/RigidBodyEngine/CollisionDetection/NarrowPhaseFilter.cpp
        src/RigidBodyEngine/CollisionDetection/Octree.cpp
        src/RigidBodyEngine/CollisionDetection/OctreeBroadPhaseFilter.cpp

        src/RigidBodyEngine/CollisionResolution/CollisionResolver.cpp
        src/RigidBodyEngine/CollisionResolution/FrictionResolver.cpp
        src/RigidBodyEngine/CollisionResolution/ICollisionResolutionFilter.cpp
        src/RigidBodyEngine/CollisionResolution/ICollisionResolverAccess.cpp
        src/RigidBodyEngine/CollisionResolution/InterpenetrationResolver.cpp
        src/RigidBodyEngine/CollisionResolution/VelocityResolver.cpp

        src/RigidBodyEngine/AnchoredSpring.cpp
        src/RigidBodyEngine/BoundingBox.cpp
        src/RigidBodyEngine/BoundingSphere.cpp
        src/RigidBodyEngine/BVHNode.cpp
        src/RigidBodyEngine/CollisionBox.cpp
        src/RigidBodyEngine/CollisionCallback.cpp
        src/RigidBodyEngine/CollisionObject.cpp
        src/RigidBodyEngine/CollisionPlane.cpp
        src/RigidBodyEngine/CollisionPrimitive.cpp
        src/RigidBodyEngine/CollisionSphere.cpp
        src/RigidBodyEngine/ComputationInterfaceFactory.cpp
        src/RigidBodyEngine/DefaultRigidBodyEngineCI.cpp
        src/RigidBodyEngine/DirectedForce.cpp
        src/RigidBodyEngine/ForceRegistry.cpp
        src/RigidBodyEngine/Gravity.cpp
        src/RigidBodyEngine/PhysicsMaterial.cpp
        src/RigidBodyEngine/RigidBody.cpp
        src/RigidBodyEngine/RigidBodyDef.cpp
        src/RigidBodyEngine/RigidBodyDef.cpp
        src/RigidBodyEngine/RigidBodyEngineCI.cpp
        src/RigidBodyEngine/RigidBodyWorld.cpp
        src/RigidBodyEngine/Spring.cpp
        
        src/Utility/Random.cpp
        src/Utility/InertiaTensorGenerator.cpp

        src/IComputationInterface.cpp
        src/PhysicsEngine.cpp
        src/PhysicsEngineModule.cpp
        src/Transform3D.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        glm
)
target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)