cmake_minimum_required(VERSION 3.14)
project(MapGrabber VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include folders
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party
    /usr/include
)

# Define the main executable and source files
add_executable(main
    src/ui/main.cpp
    src/infrastructure/CesiumConfig.cpp
    src/infrastructure/CesiumAPI.cpp
    src/infrastructure/Geocode.cpp
)

# Find system-installed libcurl
find_package(CURL REQUIRED)
target_link_libraries(main PRIVATE CURL::libcurl)

# Link libpostal manually
find_library(LIBPOSTAL_LIB postal)
if (NOT LIBPOSTAL_LIB)
    message(FATAL_ERROR "libpostal not found")
endif()
target_link_libraries(main PRIVATE ${LIBPOSTAL_LIB})
