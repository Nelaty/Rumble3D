
macro(r3d_configure_version MAJOR MINOR PATCH PRE_RELEASE BUILD_ID)
    set(R3D_VERSION_MAJOR ${MAJOR})
    set(R3D_VERSION_MINOR ${MINOR})
    set(R3D_VERSION_PATCH ${PATCH})
    set(R3D_VERSION_PRERELEASE ${PRE_RELEASE})
    set(R3D_VERSION_BUILD_ID ${BUILD_ID})

    # Build the library version according to 'semver.org'
    set(R3D_VERSION "${R3D_VERSION_MAJOR}.${R3D_VERSION_MINOR}.${R3D_VERSION_PATCH}")
    if(R3D_VERSION_PRERELEASE)
        set(R3D_VERSION "${R3D_VERSION}-${R3D_VERSION_PRERELEASE}")
    endif()
    if(R3D_VERSION_BUILD_ID)
        set(R3D_VERSION "${R3D_VERSION}+${R3D_VERSION_BUILD_ID}")
    endif()

    # Make the library versions available to other cmake projects
    get_directory_property(hasParent PARENT_DIRECTORY)
    if(hasParent)
        set(R3D_VERSION_MAJOR ${R3D_VERSION_MAJOR} PARENT_SCOPE)
        set(R3D_VERSION_MINOR ${R3D_VERSION_MINOR} PARENT_SCOPE)
        set(R3D_VERSION_PATCH ${R3D_VERSION_PATCH} PARENT_SCOPE)
        set(R3D_VERSION_PRERELEASE ${R3D_VERSION_PRERELEASE} PARENT_SCOPE)
        set(R3D_VERSION_BUILD_ID ${R3D_VERSION_BUILD_ID} PARENT_SCOPE)
        set(R3D_VERSION ${R3D_VERSION} PARENT_SCOPE)
    endif()
endmacro()