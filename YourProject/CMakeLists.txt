cmake_minimum_required(VERSION 3.14)
project(YourProjectName VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include/ and src/ as global include paths
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Add subdirectories (for modular growth)
add_subdirectory(src)
add_subdirectory(tests)

# Main app entry
add_executable(main src/ui/main.cpp)

# Link includes from src and include folders
target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Optionally link libs or dependencies here if needed later
# target_link_libraries(main ...)
