cmake_minimum_required(VERSION 3.8...3.28)

# Fallback for using newer policies on CMake <3.12.
if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

project(cgif C)
include(GNUInstallDirs)

option(CGIF_SYSTEM_HEADERS "Expose headers with marking them as system." OFF)
option(CGIF_INSTALL "Generate the install target." OFF)

set(CGIF_SYSTEM_HEADERS_ATTRIBUTE "")
if (CGIF_SYSTEM_HEADERS)
  set(CGIF_SYSTEM_HEADERS_ATTRIBUTE SYSTEM)
endif ()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "")


set(CGIF_HEADERS inc/cgif.h inc/cgif_raw.h)
set(CGIF_SOURCES src/cgif.c src/cgif_raw.c)

add_library(cgif_lib SHARED src/cgif.c inc/cgif.h src/cgif_raw.c inc/cgif_raw.h)
add_library(cgif::cgif ALIAS cgif_lib)
set_target_properties(
  cgif_lib
  PROPERTIES VERSION 0.4.0
             SOVERSION 1
             LINKER_LANGUAGE C
)

target_include_directories(
  cgif_lib ${CGIF_SYSTEM_HEADERS_ATTRIBUTE} BEFORE PUBLIC 
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
  $<INSTALL_INTERFACE:${CGIF_INC_DIR}>
)

install(
  TARGETS cgif_lib
  EXPORT PixelmancyTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include
)


if (CGIF_INSTALL)
  include(CMakePackageConfigHelpers)

  set(version_config ${PROJECT_BINARY_DIR}/fmt-config-version.cmake)
  set(project_config ${PROJECT_BINARY_DIR}/fmt-config.cmake)
  set(pkgconfig ${PROJECT_BINARY_DIR}/fmt.pc)
  set(targets_export_name fmt-targets)


  # Generate the version, config and target files into the build directory.
  write_basic_package_version_file(
    ${version_config}
    VERSION ${FMT_VERSION}
    COMPATIBILITY AnyNewerVersion)

  join_paths(libdir_for_pc_file "\${exec_prefix}" "${FMT_LIB_DIR}")
  join_paths(includedir_for_pc_file "\${prefix}" "${FMT_INC_DIR}")

  configure_file(
    "${PROJECT_SOURCE_DIR}/support/cmake/fmt.pc.in"
    "${pkgconfig}"
    @ONLY)
  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/support/cmake/fmt-config.cmake.in
    ${project_config}
    INSTALL_DESTINATION ${FMT_CMAKE_DIR})

  set(INSTALL_TARGETS fmt fmt-header-only)

  set(INSTALL_FILE_SET)
  if (FMT_USE_CMAKE_MODULES)
    set(INSTALL_FILE_SET FILE_SET fmt DESTINATION "${FMT_INC_DIR}/fmt")
  endif()

  # Install the library and headers.
  install(TARGETS ${INSTALL_TARGETS}
          COMPONENT fmt-core
          EXPORT ${targets_export_name}
          LIBRARY DESTINATION ${FMT_LIB_DIR}
          ARCHIVE DESTINATION ${FMT_LIB_DIR}
          PUBLIC_HEADER DESTINATION "${FMT_INC_DIR}/fmt"
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          ${INSTALL_FILE_SET})

  # Use a namespace because CMake provides better diagnostics for namespaced
  # imported targets.
  export(TARGETS ${INSTALL_TARGETS} NAMESPACE fmt::
         FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)

  # Install version, config and target files.
  install(FILES ${project_config} ${version_config}
          DESTINATION ${FMT_CMAKE_DIR}
          COMPONENT fmt-core)
  install(EXPORT ${targets_export_name} DESTINATION ${FMT_CMAKE_DIR}
          NAMESPACE fmt::
          COMPONENT fmt-core)

  install(FILES "${pkgconfig}" DESTINATION "${FMT_PKGCONFIG_DIR}"
          COMPONENT fmt-core)
endif ()