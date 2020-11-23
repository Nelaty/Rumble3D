file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "../include/*.h" "../include/*.hpp")
file(GLOB_RECURSE inline_files "../include/*.inl")

set(all_sources ${source_files}
		${header_files}
		${inline_files})

add_executable(${PROJECT_NAME}_Example
	${all_sources}
)

add_dependencies(${PROJECT_NAME}_Example ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})

