# tests/CMakeLists.txt

# Find or fetch GoogleTest if needed
# (You can add FetchContent here, or use system-installed GTest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(run_tests PRIVATE core)  # if you made a `core` lib
# target_link_libraries(run_tests PRIVATE gtest gtest_main)  # if using GTest

add_test(NAME AllTests COMMAND run_tests)
