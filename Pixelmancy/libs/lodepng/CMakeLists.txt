project(lodepng)
add_library(
  lodepng SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.cpp ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.h
)
set_target_properties(lodepng PROPERTIES VERSION 1.0.0 SOVERSION 1)
set(CMAKE_CXX_STANDARD 17)

target_include_directories(
  lodepng PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                 $<INSTALL_INTERFACE:include/lodepng-${PROJECT_VERSION}>
)

install(
  TARGETS lodepng
  EXPORT PixelmancyTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)
