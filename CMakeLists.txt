#
# Copyright (c) 2022 Eureka Robotics
# Authors: Joseph Mirabel
#
#

cmake_minimum_required(VERSION 3.22)

set(CXX_DISABLE_WERROR TRUE)
set(DOXYGEN_USE_MATHJAX YES)
set(DOXYGEN_USE_TEMPLATE_CSS TRUE)
set(PROJECT_USE_CMAKE_EXPORT TRUE)

set(PROJECT_NAME hpp-toppra)
set(PROJECT_DESCRIPTION "Bridge between HPP and TOPPRA.")

find_package(jrl-cmakemodules QUIET CONFIG)
if(jrl-cmakemodules_FOUND)
  get_property(
    JRL_CMAKE_MODULES
    TARGET jrl-cmakemodules::jrl-cmakemodules
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
  message(STATUS "JRL cmakemodules found on system at ${JRL_CMAKE_MODULES}")
else()
  message(STATUS "JRL cmakemodules not found. Let's fetch it.")
  include(FetchContent)
  FetchContent_Declare(
    "jrl-cmakemodules"
    GIT_REPOSITORY "https://github.com/jrl-umi3218/jrl-cmakemodules.git")
  FetchContent_MakeAvailable("jrl-cmakemodules")
  FetchContent_GetProperties("jrl-cmakemodules" SOURCE_DIR JRL_CMAKE_MODULES)
endif()

include("${JRL_CMAKE_MODULES}/hpp.cmake")
include("${JRL_CMAKE_MODULES}/boost.cmake")

compute_project_args(PROJECT_ARGS LANGUAGES CXX)
project(${PROJECT_NAME} ${PROJECT_ARGS})

set(CMAKE_CXX_STANDARD 14)
add_project_dependency(eigenpy REQUIRED)
add_project_dependency(hpp-core REQUIRED)
add_project_dependency(hpp-manipulation REQUIRED)
add_project_dependency(toppra 0.6.2 REQUIRED)

include(${HPP_CORE_CMAKE_PLUGIN})

set(${PROJECT_NAME}_HEADERS
  include/hpp/toppra/toppra.hh
)

add_library(${PROJECT_NAME}
  SHARED
  src/toppra.cc
  src/piecewise-polynomial.hh
  src/piecewise-polynomial.hh
  src/serialization.hh
  ${${PROJECT_NAME}_HEADERS}
)
target_link_libraries(hpp-toppra PUBLIC hpp-core::hpp-core toppra::toppra)
target_include_directories(hpp-toppra PUBLIC $<INSTALL_INTERFACE:include>)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION lib)

message(STATUS "Found toppra ${toppra_VERSION}")

add_subdirectory(python)

add_executable(unittests
  tests/tests.cc
  tests/test-ill-formed-paths.cc
  tests/test-path-serialization.cc
)
add_test(unittests unittests)
target_link_libraries(unittests hpp-manipulation::hpp-manipulation toppra::toppra hpp-toppra)# Catch2::Catch2)
