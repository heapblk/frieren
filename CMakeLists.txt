cmake_minimum_required(VERSION 3.15)

project(frieren VERSION 1.0 LANGUAGES CXX)

# Options
option(BUILD_SHARED "Build shared library" ON)
option(BUILD_STATIC "Build static library" ON)

# the c++17 standard is widely supported, thats why its the defaut here
set(CMAKE_CXX_STANDARD 17)

# paths
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# sources
set(HEADER_FILES
        "${INCLUDE_DIR}/physics/Forces.h"
        "${INCLUDE_DIR}/physics/Gravity.h"

        "${INCLUDE_DIR}/aircraft/State.h"
        "${INCLUDE_DIR}/aircraft/Params.h"

        "${INCLUDE_DIR}/simulator/Simulator.h"
)

set(SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/physics/Gravity.cpp"

        "${CMAKE_CURRENT_SOURCE_DIR}/src/simulator/Simulator.cpp"
)

# publicly exposed header files
set(EXPORT_FILES
        "${INCLUDE_DIR}/physics/Gravity.h"
        "${INCLUDE_DIR}/aircraft/State.h"
        "${INCLUDE_DIR}/aircraft/Params.h"
        "${INCLUDE_DIR}/simulator/Simulator.h"
)

# build as shared lib
if(BUILD_SHARED)
    add_library(frieren_shared SHARED ${SOURCE_FILES})
    set_target_properties(frieren_shared PROPERTIES OUTPUT_NAME "frieren_shared")
    target_include_directories(frieren_shared PUBLIC
			"$<BUILD_INTERFACE:${INCLUDE_DIR}>"
			"$<INSTALL_INTERFACE:include>"
	)
    add_library(frieren::frieren_shared ALIAS frieren_shared)
endif()

# build as static lib
if(BUILD_STATIC)
    add_library(frieren_static STATIC ${SOURCE_FILES})
    set_target_properties(frieren_static PROPERTIES OUTPUT_NAME "frieren")
    target_include_directories(frieren_static PUBLIC
			"$<BUILD_INTERFACE:${INCLUDE_DIR}>"
			"$<INSTALL_INTERFACE:include>"
	)
    add_library(frieren::frieren_static ALIAS frieren_static)
endif()

# installation
include(GNUInstallDirs)

# install headers
install(FILES ${EXPORT_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install libraries
if(BUILD_SHARED)
    install(TARGETS frieren_shared
        EXPORT frierenTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

if(BUILD_STATIC)
    install(TARGETS frieren_static
        EXPORT frierenTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

# export targets for find_package
install(EXPORT frierenTargets
    FILE frierenTargets.cmake
    NAMESPACE frieren::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/frieren"
)

# generate frierenConfig.cmake and frierenConfigVersion.cmake
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/frierenConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/frierenConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/frierenConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/frieren"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/frierenConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/frierenConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/frieren"
)

# setup GoogleTest
enable_testing()
find_package(GTest)

add_executable(tests "test/main.cpp" 
	"test/simulator.cpp"
)

if(BUILD_STATIC)
    target_link_libraries(tests PRIVATE frieren_static GTest::gtest_main)
elseif(BUILD_SHARED)
    target_link_libraries(tests PRIVATE frieren_shared GTest::gtest_main)
endif()
target_include_directories(tests PRIVATE "../lib/include")

include(GoogleTest)
gtest_discover_tests(tests)
