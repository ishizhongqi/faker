cmake_minimum_required(VERSION 3.22)

project(faker_example CXX)

set(EXAMPLE_SOURCES
        main.cpp
)

add_executable(faker_example ${EXAMPLE_SOURCES})

set(TEST_COMPILE_FEATURES cxx_std_20)

target_link_libraries(faker_example
    PRIVATE
        faker
)

target_compile_features(faker_example PRIVATE ${TEST_COMPILE_FEATURES})

target_include_directories(faker_example
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
