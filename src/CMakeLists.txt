file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.h" "*.hpp")
file(GLOB_RECURSE inline_files "*.inl")

set(all_sources ${source_files}
        ${header_files}
        ${inline_files})

add_library(${PROJECT_NAME} STATIC ${all_sources})