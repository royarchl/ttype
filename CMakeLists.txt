cmake_minimum_required(VERSION 3.10)
project(ttype VERSION 1.0)

# Specify C++ standard to use
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
  src/gap-buffer.cc
  src/main.cc
)

# Put executables in bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define the executable target for the main application
add_executable(my_app ${SOURCES})

# Define the executable target for the tests application
add_executable(gap_buffer_test tests/gap-buffer_test.cc src/gap-buffer.cc)

# Add Google Test
add_subdirectory(external/googletest)

# Link the Google Test library to the test executable
target_link_libraries(gap_buffer_test gtest_main)

# Add FTXUI
add_subdirectory(external/FTXUI)

# Link FTXUI components to main application
target_link_libraries(my_app
  # Using 'PRIVATE' assigns the dependency only to my_app
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)

# (optionally) link to the test exectuable
# target_link_libraries(gap_buffer_test ...)

# Include directories for source files
target_include_directories(my_app PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(gap_buffer_test PRIVATE ${CMAKE_SOURCE_DIR}/src)


# Additional compilation options

# Put .o files in obj/
set_target_properties(my_app PROPERTIES
  OBJECT_OUTPUTS ${CMAKE_BINARY_DIR}/obj
)
