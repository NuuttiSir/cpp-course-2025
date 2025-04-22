include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

file(
  GLOB
  sources
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_colour.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_image.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_frame.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_gif.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_shapes.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/test_lines.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/common.hpp
  ${CMAKE_BINARY_DIR}/test_config.hpp
)

configure_file(src/test_config.hpp.in test_config.hpp)
configure_file(naruto.png naruto.png COPYONLY)
configure_file(dog.png dog.png COPYONLY)
configure_file(tree.png tree.png COPYONLY)
configure_file(lettuce.png lettuce.png COPYONLY)

add_executable(PixelmancyTests ${sources})
target_link_libraries(PixelmancyTests PRIVATE Catch2::Catch2WithMain Pixelmancy)
target_include_directories(PixelmancyTests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(PixelmancyTests PROPERTIES CXX_STANDARD 17)

if(PIXELMANCY_ENABLE_PCH)
  include(../cmake/cotire.cmake)
  cotire(PixelmancyTests)
endif()

enable_testing()

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(PixelmancyTests)

# ---- code coverage ----
