cmake_minimum_required(VERSION 3.22)
project(faker_ut CXX)

include(CTest)
include(CompilerWarnings)
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

set(UT_SOURCES
        modules/test_business.cpp
        modules/test_computer.cpp
        modules/test_datetime.cpp
        modules/test_location.cpp
        modules/test_number.cpp
        modules/test_payment.cpp
        modules/test_person.cpp
        modules/test_product.cpp
        modules/test_string.cpp
        utils/test_random_helper.cpp
        utils/test_string_helper.cpp
        utils/test_validation.cpp
        types/test_bilingual.cpp
)

add_executable(faker_ut ${UT_SOURCES})

set_project_warnings(faker_ut
        "${WARNINGS_AS_ERRORS}"
        "${MSVC_WARNINGS}"
        "${CLANG_WARNINGS}"
        "${GCC_WARNINGS}"
)

target_include_directories(faker_ut PRIVATE
        ./tests_helper/
        ../src/core
        ../src/utils
        ../src/modules/business
        ../src/modules/computer
        ../src/modules/location
        ../src/modules/payment
        ../src/modules/person
        ../src/modules/product
        ../src/modules/string
)

set(TEST_COMPILE_FEATURES cxx_std_20)

target_link_libraries(faker_ut
        PRIVATE
        faker
        GTest::gtest_main
)

target_compile_features(faker_ut PRIVATE ${TEST_COMPILE_FEATURES})

gtest_discover_tests(faker_ut)

if (CODE_COVERAGE)
    target_code_coverage(faker_ut ALL)
endif ()
