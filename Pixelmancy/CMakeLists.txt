cmake_minimum_required(VERSION 3.14...3.30)
project(
  Pixelmancy
  VERSION 0.9.0
  DESCRIPTION "A simple gif creator"
  LANGUAGES CXX
)

# inspired by https://github.com/TheLartians/ModernCppStarter

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PIXELMANCY_BUILD_TESTS "Enable tests" OFF)
option(PIXELMANCY_ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(PIXELMANCY_ENABLE_CHECKS "Enable clang-tidy" OFF)
option(PIXELMANCY_ENABLE_FORMATTERS "Enable formatters" OFF)
option(PIXELMANCY_ENABLE_PCH "Enable precompiled headers" OFF)
option(PIXELMANCY_ENABLE_PRE_BUILD_LIBS "Enable precompiled libraries" ON)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
  if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
  endif()
else()
  set(allowedBuildTypes Asan Debug Release RelWithDebInfo MinSizeRel)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

  if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
  endif()
endif()

set(CMAKE_C_FLAGS_ASAN
    "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer"
    CACHE STRING "Flags used by the C compiler for Asan build type or configuration." FORCE
)

set(CMAKE_CXX_FLAGS_ASAN
    "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer"
    CACHE STRING "Flags used by the C++ compiler for Asan build type or configuration." FORCE
)

set(CMAKE_EXE_LINKER_FLAGS_ASAN
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address"
    CACHE STRING "Linker flags to be used to create executables for Asan build type." FORCE
)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address"
    CACHE STRING "Linker lags to be used to create shared libraries for Asan build type." FORCE
)

# add optimize flags for release builds
set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} -Os -s -fno-ident -fno-asynchronous-unwind-tables"
)
set(CMAKE_C_FLAGS_RELEASE
    "${CMAKE_C_FLAGS_RELEASE} -Os -s -fno-ident -fno-asynchronous-unwind-tables"
)

# disable optimizations for non-release builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O0")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -O0")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -O0")
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -O0")

if(PIXELMANCY_ENABLE_FORMATTERS)
  include(cmake/CPM.cmake)
  CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")
endif()

file(GLOB_RECURSE logger_headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/logger/*.hpp")
file(GLOB_RECURSE logger_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/logger/*.cpp")
add_library(logger OBJECT ${logger_headers} ${logger_sources})

file(GLOB_RECURSE colors_headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/colors/*.hpp")
file(GLOB_RECURSE colors_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/colors/*.cpp")
add_library(colors OBJECT ${colors_headers} ${colors_sources})

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/logger/*.hpp"
)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_subdirectory(libs)
add_library(${PROJECT_NAME} ${headers} ${sources})

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

find_package(fmt QUIET)
if(fmt_FOUND)
  message(STATUS "Using prebuilt fmt library")
endif()

find_package(lodepng QUIET)
if(lodepng_FOUND)
  message(STATUS "Using prebuilt lodepng library")
endif()

target_link_libraries(colors PUBLIC fmt::fmt logger)
target_include_directories(colors PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/logger>)
target_link_libraries(${PROJECT_NAME} PUBLIC cgif_lib lodepng fmt::fmt logger colors)

# disable compiler warnings from fmt library
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE libs/fmt-11.1.3/include/)

if(PIXELMANCY_ENABLE_CHECKS)
  include(cmake/CPM.cmake)
  include(cmake/tools.cmake)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(
      ${PROJECT_NAME}
      PRIVATE -Wall
              -Wextra
              -pedantic
              -pedantic-errors
              -Wshadow
              -Wnon-virtual-dtor
              -Wold-style-cast
              -Wcast-align
              -Wnull-dereference
              -Woverloaded-virtual
              -Wuseless-cast
              -Wpedantic
              -Wunused
              -Wconversion
              -Wdouble-promotion
              -Wformat=2
              # -Wlifetime
              -Wimplicit-fallthrough
              -Wlogical-op
              -Wduplicated-branches
              -Wduplicated-cond
              -Wsign-conversion
    )
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
  endif()
endif()

if(PIXELMANCY_ENABLE_PCH)
  include(cmake/cotire.cmake)
  cotire(${PROJECT_NAME})
endif()

add_subdirectory(standalone)

if(PIXELMANCY_BUILD_TESTS)
  include(CTest)
  add_subdirectory(tests)
endif()
