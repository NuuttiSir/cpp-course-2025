# config files
configure_file(config.hpp.in config.hpp)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../libs/pre-built)

add_executable(PixelmancyExample main.cpp)
target_include_directories(PixelmancyExample PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(PixelmancyExample PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "PixelmancyExample")

find_package(cxxopts QUIET)
if(cxxopts_FOUND)
  message(STATUS "Using prebuilt cxxopts library")
  target_link_libraries(PixelmancyExample PRIVATE cxxopts::cxxopts)
else()
  message(STATUS "cxxopts not found")
  target_link_libraries(PixelmancyExample PRIVATE cxxopts)
endif()

target_link_libraries(PixelmancyExample PRIVATE Pixelmancy)
