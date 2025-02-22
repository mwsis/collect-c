
# ######################################################################## #
# File:     /CMakeLists.txt
#
# Purpose:  Top-level CMake lists file for collect-c
#
# Created:  4th February 2025
# Updated:  11fth February 2025
#
# ######################################################################## #


# ##########################################################
# CMake

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# require out-of-source builds
file(TO_CMAKE_PATH "${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")

	message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# directory for CMake specific extensions and source files.
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


# ##########################################################
# project

project(collect-c
	DESCRIPTION "Special and custom Collections and Containers (for C++)"
	HOMEPAGE_URL "https://github.com/synesissoftware/collect-c"
	LANGUAGES C CXX
)

string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

# handle version number
set(RX_PROJ_TAG "COLLECT_C")
set(RX_WS "[ \t]")
file(READ "${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/common/version.h" _header_file)
string(REGEX MATCH "#${RX_WS}*define${RX_WS}+_?${RX_PROJ_TAG}_VER_MAJOR${RX_WS}+([0-9]+)" MAJOR_DUMMY ${_header_file})
set(_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#${RX_WS}*define${RX_WS}+_?${RX_PROJ_TAG}_VER_MINOR${RX_WS}+([0-9]+)" MINOR_DUMMY ${_header_file})
set(_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#${RX_WS}*define${RX_WS}+_?${RX_PROJ_TAG}_VER_PATCH${RX_WS}+([0-9]+)" PATCH_DUMMY ${_header_file})
set(_VERSION_PATCH ${CMAKE_MATCH_1})

# set project version number here
set(PROJECT_VERSION_MAJOR ${_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${_VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${_VERSION_PATCH})
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")


# adhere strictly to C and C++ standards plus extensions. These are actually
# useless since we do not compile anything; they merely state our intention.
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON) # GNU extensions and POSIX standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


if(MSVC)

	if(MSVC_VERSION LESS 1930)

		set(CMAKE_C_STANDARD 90)
		set(CMAKE_CXX_STANDARD 98)
	endif()
endif(MSVC)


# ##########################################################
# dependencies, includes, options

# ################################################
# includes - 1

include(BuildType)
include(LanguageFullVersion)
include(TargetMacros)


# ################################################
# dependencies and options

option(BUILD_EXAMPLES "Build examples" ON)


# ######################################
# dependencies
#
# required:
# - cstring - required for testing;
# - Diagnosticism - required for testing;
# - STLSoft - required for testing;
# - xTests - required for testing;
#
# optional:
# - shwild - required for testing;
#


# ############################
# cstring

if(BUILD_TESTING)

	set(cstring_REQUIRED_VERSION_ 0.0)

	find_package(cstring ${cstring_REQUIRED_VERSION_} REQUIRED)

	message("-- CMake package cstring found (version ${cstring_VERSION}; ${cstring_REQUIRED_VERSION_} requested)")
endif(BUILD_TESTING)


# ############################
# Diagnosticism

if(BUILD_TESTING)

	set(Diagnosticism_REQUIRED_VERSION_ 0.0)

	find_package(Diagnosticism ${Diagnosticism_REQUIRED_VERSION_} REQUIRED)

	message("-- CMake package Diagnosticism found (version ${Diagnosticism_VERSION}; ${Diagnosticism_REQUIRED_VERSION_} requested)")
endif(BUILD_TESTING)


# ############################
# STLSoft

if(BUILD_TESTING)

	if(DEFINED STLSOFT)

		message("-- STLSOFT provided as CMake variable with value '${STLSOFT}'")

		set(STLSOFT_INCLUDE_DIR ${STLSOFT}/include)
	elseif(DEFINED ENV{STLSOFT})

		message("-- STLSOFT provided as environment variable with value '$ENV{STLSOFT}'")

		set(STLSOFT_INCLUDE_DIR $ENV{STLSOFT}/include)
	else()

		set(STLSoft_REQUIRED_VERSION_ 1.11)

		find_package(STLSoft ${STLSoft_REQUIRED_VERSION_} REQUIRED)

		message("-- CMake package STLSoft found (version ${STLSoft_VERSION}; ${STLSoft_REQUIRED_VERSION_} requested)")
	endif()

	if(DEFINED STLSOFT_INCLUDE_DIR)

		include_directories(${STLSOFT_INCLUDE_DIR})
	endif()
endif(BUILD_TESTING)


# ############################
# shwild

if(BUILD_TESTING)

	find_package(shwild QUIET)

	message("-- CMake package shwild found (version ${shwild_VERSION})")
endif(BUILD_TESTING)


# ############################
# xTests

if(BUILD_TESTING)

	set(xTests_REQUIRED_VERSION_ 0.26)

	find_package(xTests ${xTests_REQUIRED_VERSION_} REQUIRED)

	message("-- CMake package xTests found (version ${xTests_VERSION}; ${xTests_REQUIRED_VERSION_} requested)")
endif(BUILD_TESTING)


# ################################################
# includes - 2

include(CMakePackageConfigHelpers)
if(BUILD_TESTING)

	include(CTest)
endif(BUILD_TESTING)
include(GNUInstallDirs)


# ##########################################################
# targets

# ################################################
# main library

add_subdirectory(src)


# ################################################
# examples

if(BUILD_EXAMPLES)

	message("-- enabled building of examples ...")

	add_subdirectory(examples)
else(BUILD_EXAMPLES)

	message("-- disabled building of examples - define BUILD_EXAMPLES to enable")
endif(BUILD_EXAMPLES)


# ################################################
# tests

if(BUILD_TESTING)

	message("-- enabled building of tests ...")

	add_subdirectory(test)
else(BUILD_TESTING)

	message("-- disabled building of tests - define BUILD_TESTING to enable")
endif(BUILD_TESTING)


# ##########################################################
# install


# ##########################################################
# export

set(EXPORT_NAME ${PROJECT_NAME_LOWER})

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/${EXPORT_NAME}-config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config.cmake
	INSTALL_DESTINATION ${LIB_INSTALL_DIR}/${EXPORT_NAME}/cmake
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config-version.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)

export(EXPORT project-targets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-targets.cmake"
	NAMESPACE "${PROJECT_NAME}::"
)

install(EXPORT project-targets
	NAMESPACE "${PROJECT_NAME}::"
	FILE "${EXPORT_NAME}-targets.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
)

install( FILES
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${EXPORT_NAME}-config-version.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
)


# ##########################################################
# completion

message(NOTICE "Generating CMake build scripts for ${PROJECT_NAME} ${PROJECT_VERSION}, for C${CMAKE_C_STANDARD} C++${CMAKE_CXX_STANDARD}")


# ############################## end of file ############################# #

