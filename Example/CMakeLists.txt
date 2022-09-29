add_executable(${PROJECT_NAME}_Example
	src/main
)

target_link_libraries(${PROJECT_NAME}_Example 
	PRIVATE
	    ${PROJECT_NAME}
)
