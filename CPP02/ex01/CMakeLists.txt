cmake_minimum_required(VERSION 3.10)
project(ex01 CXX)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard to C++98
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # disable compiler-specific extensions like gnu++98

# Enable strict compiler warnings
add_compile_options(-Wall -Wextra -Werror)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect source files
file(GLOB_RECURSE SRC_FILES
  ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# declare a target (no build will be done unless you invoke it)
add_executable(${PROJECT_NAME} ${SRC_FILES})
