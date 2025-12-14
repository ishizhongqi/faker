cmake_minimum_required(VERSION 3.22)

set(FAKER_SOURCES
        types/bilingual.cpp
        core/random_engine.cpp
        utils/random_helper.cpp
        utils/string_helper.cpp
        utils/validation.cpp
        modules/business/business.cpp
        modules/computer/computer.cpp
        modules/datetime/datetime.cpp
        modules/location/location.cpp
        modules/number/number.cpp
        modules/payment/payment.cpp
        modules/person/person.cpp
        modules/product/product.cpp
        modules/string/string.cpp
)

set(FAKER_HEADERS
        core/random_engine.h
        utils/random_helper.h
        utils/string_helper.h
        utils/validation.h
        modules/business/business_data.h
        modules/computer/computer_data.h
        modules/location/location_data.h
        modules/payment/payment_data.h
        modules/person/person_data.h
        modules/product/product_data.h
        modules/string/string_data.h
)

target_sources(faker PRIVATE ${FAKER_SOURCES} ${FAKER_HEADERS})

target_include_directories(faker
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(faker
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        ${PROJECT_SOURCE_DIR}/src/core
        ${PROJECT_SOURCE_DIR}/src/utils
        ${PROJECT_SOURCE_DIR}/src/modules/business
        ${PROJECT_SOURCE_DIR}/src/modules/computer
        ${PROJECT_SOURCE_DIR}/src/modules/location
        ${PROJECT_SOURCE_DIR}/src/modules/payment
        ${PROJECT_SOURCE_DIR}/src/modules/person
        ${PROJECT_SOURCE_DIR}/src/modules/product
        ${PROJECT_SOURCE_DIR}/src/modules/string
)

include(CompilerWarnings)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

target_compile_features(faker PUBLIC cxx_std_20)

set_project_warnings(faker
        "${WARNINGS_AS_ERRORS}"
        "${MSVC_WARNINGS}"
        "${CLANG_WARNINGS}"
        "${GCC_WARNINGS}"
)

configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/version.h.in"
        "${CMAKE_BINARY_DIR}/include/faker/version.h"
        @ONLY
)

set_target_properties(faker PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        CMAKE_VISIBILITY_INLINES_HIDDEN 1
        VERSION ${CMAKE_PROJECT_VERSION}
        SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
)

target_include_directories(
        faker
        PUBLIC $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        PRIVATE ${CMAKE_BINARY_DIR}/include
)

configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/faker.pc.in"
        "${CMAKE_BINARY_DIR}/faker.pc"
        @ONLY
)

write_basic_package_version_file(${PROJECT_BINARY_DIR}/fakerConfigVersion.cmake
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

# Install compiled library
install(
        TARGETS faker
        EXPORT fakerTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/faker
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.h"
)

install(DIRECTORY ${CMAKE_BINARY_DIR}/include/faker
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING
        PATTERN "*.h"
)

install(FILES "${CMAKE_BINARY_DIR}/faker.pc"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

install(FILES
        "${CMAKE_BINARY_DIR}/fakerConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

# Export targets for CMake find_package
install(
        EXPORT fakerTargets
        FILE fakerTargets.cmake
        NAMESPACE faker::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)
