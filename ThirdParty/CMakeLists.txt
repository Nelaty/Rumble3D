###############################################################################
# Catch2
###############################################################################
if(NOT TARGET Catch2)
    message("Adding catch2 library")
    set(CATCH_BUILD_TESTING OFF)
    set(CATCH_BUILD_EXAMPLES OFF)
    set(CATCH_INSTALL_DOCS OFF)
    set(CATCH_INSTALL_EXTRAS OFF)

    add_subdirectory(Catch2)
endif()

###############################################################################
# glm
###############################################################################
if(NOT TARGET glm)
    message("Adding glm library")
    add_subdirectory(glm)
endif()
