file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.hpp" "*.h")
file(GLOB_RECURSE inline_files "*.inl")

set(all_source_files ${source_files} ${header_files} ${inline_files})

add_executable(${RUMBLE3D_TEST_NAME} ${all_source_files})
target_link_libraries(${RUMBLE3D_TEST_NAME} ${RUMBLE3D_LIB_NAME})
target_include_directories(${RUMBLE3D_TEST_NAME} PUBLIC ${RUMBLE_INCLUDE_DIRECTORY} "include/")