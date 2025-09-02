# CMake build for etc2comp
#
# Original project by Google
# Functional improvements by Alec Miller (alecmiller@yahoo.com) as part of kram
# Current CMake implementation and minor tweaks by Christian Heimlich (chris@pcserenity.com)

#================= Project Setup ==========================

# CMake
cmake_minimum_required(VERSION 3.23.0...3.31.0)

# Project
# NOTE: DON'T USE TRAILING ZEROS IN VERSIONS
project(etc2comp
    VERSION 1.0
    LANGUAGES CXX
    DESCRIPTION "Ericsson Texture Compression codec library"
)

# Get helper scripts
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FetchOBCMake.cmake)
fetch_ob_cmake("v0.3.9.1")

# Initialize project according to standard rules
include(OB/Project)
ob_standard_project_setup(
    NAMESPACE "Etc"
)

# Configuration options
option(BUILD_SHARED_LIBS "Build shared libraries." OFF) # Redundant due to OB, but explicit

# C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#================= Build =========================

# Target - Lib
set(LIB_TARGET_NAME ${PROJECT_NAMESPACE_LC}_etc)
set(LIB_ALIAS_NAME Etc)
set(LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${LIB_PATH}")

#--------------------Package Config-----------------------

ob_standard_project_package_config(
    COMPATIBILITY "SameMajorVersion"
    CONFIG STANDARD
        TARGET_CONFIGS
            TARGET "${PROJECT_NAMESPACE}::${LIB_ALIAS_NAME}" COMPONENT "${LIB_ALIAS_NAME}" DEFAULT
)

#================= Install ==========================

ob_standard_project_misc_install()

#====================== CPack ==============================

include(OB/Packaging)
ob_standard_project_package(VENDOR "oblivioncth")
