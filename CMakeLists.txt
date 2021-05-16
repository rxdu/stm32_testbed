cmake_minimum_required(VERSION 3.10.2)

## check whether ccache exists for faster compile
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(stm32_testbed C CXX ASM)

#############################################################

## choose the board
if(NOT DEFINED BOARD_NAME)
set(BOARD_NAME "bbb_racer_cape")
endif()

## choose the application
# app_blink, app_racer
if(NOT DEFINED APP_NAME)
set(APP_NAME "app_racer")
endif()

## chosse build type (Debug/Release)
set(CMAKE_BUILD_TYPE Debug)

## choose debug output method (RTT/ITM/NONE)
set(DBG_OUTPUT_CHN RTT)

#############################################################

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS "---------------------------------------")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Debug output channel: ${DBG_OUTPUT_CHN}")

## Version information
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")

## set project directories
set(STM32_CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(TARGET_DIR ${CMAKE_SOURCE_DIR}/src/board)

## add source code
add_subdirectory(src)
