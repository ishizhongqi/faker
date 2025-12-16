# Copyright (c) 2025 Shizhongqi
# Licensed under the MIT License.
# See the LICENSE file in the project root for more information.

cmake_minimum_required(VERSION 3.22)
project(faker
        VERSION 0.2.0
        LANGUAGES CXX
)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dist")

# CMake module path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Build shared option
option(FAKER_BUILD_SHARED "Build shared library" OFF)

# Example option
option(FAKER_BUILD_EXAMPLE "Build example" OFF)

# Testing option
option(FAKER_BUILD_TESTS "Build tests" OFF)

# Code coverage option 
option(FAKER_CODE_COVERAGE "Build code coverage" ON)

# Export compile commands
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build shared library
if (FAKER_BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
endif ()

add_library(${PROJECT_NAME})

add_subdirectory(src)

if (BUILD_SHARED_LIBS)
    set_target_properties(faker PROPERTIES
            POSITION_INDEPENDENT_CODE ON
    )
endif ()

# Code coverage
if (FAKER_CODE_COVERAGE)
    set(CODE_COVERAGE ON) 
    set(target_code_coverage_ALL 1)
    include(code-coverage)
    add_code_coverage_all_targets(EXCLUDE tests/*)
    target_code_coverage(faker ALL)
endif ()

# Build example
if (FAKER_BUILD_EXAMPLE)
    message(STATUS "Generating example")
    add_subdirectory(example)
endif ()

# Build tests
if (FAKER_BUILD_TESTS)
    message(STATUS "Generating tests")
    enable_testing()
    add_subdirectory(tests)
endif ()
