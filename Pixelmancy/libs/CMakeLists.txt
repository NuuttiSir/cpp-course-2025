# https://stackoverflow.com/questions/74916407/can-c-projects-libraries-that-have-external-dependencies-be-configured-to-work

set(CXXOPTS_BUILD_TESTS OFF)
set(FMT_TEST OFF)
set(FMT_DOC OFF)
set(FMT_SYSTEM_HEADERS ON)
set(CGIF_SYSTEM_HEADERS ON)

if(PIXELMANCY_ENABLE_PRE_BUILD_LIBS)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/pre-built)
    
    set(CXXOPTS_ENABLE_INSTALL ON)
    set(FMT_INSTALL ON)
    set(CGIF_INSTALL OFF)

    find_package(cxxopts 3.2.0 QUIET)
    if (cxxopts_FOUND)
        message(STATUS "Using prebuilt cxxopts library")
    else()
        message(STATUS "cxxopts not found")
        add_subdirectory(cxxopts-3.2.0)
    endif()

    find_package(fmt 11.1.3 QUIET)
    if (fmt_FOUND)
        message(STATUS "Using prebuilt fmt library")
    else()
        message(STATUS "fmt not found")
        add_subdirectory(fmt-11.1.3)
    endif()

    find_package(lodepng 1.0.0 QUIET)
    if (lodepng_FOUND)
        message(STATUS "Using prebuilt lodepng library")
    else()
        message(STATUS "lodepng not found")
        add_subdirectory(lodepng)
    endif()

else()
    add_subdirectory(cxxopts-3.2.0)
    add_subdirectory(fmt-11.1.3)
    add_subdirectory(lodepng)
endif()

add_subdirectory(cgif)
