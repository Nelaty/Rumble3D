add_executable(${PROJECT_NAME}_Example
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)


add_dependencies(${PROJECT_NAME}_Example ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})

