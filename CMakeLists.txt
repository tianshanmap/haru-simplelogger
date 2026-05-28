# set minimum cmake version
cmake_minimum_required(VERSION 4.2 FATAL_ERROR)
project(simplelogger VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the library
add_library(simplelogger SHARED
        src/simple_logger.cpp
)

# Target include directories (Public for users, Private for internal source)
target_include_directories(simplelogger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
