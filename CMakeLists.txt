cmake_minimum_required(VERSION 3.5)


# ---------------------------------------------------------------------------------------
# Set default build to release
# ---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

# require at least C++20
if(NOT CMAKE_CXX_STANDARD)
    message(STATUS "CMAKE_CXX_STANDARD is not set, automatically set it to C++20")
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
elseif(CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "ezli require at least C++20!")
endif()

# ---------------------------------------------------------------------------------------
# Set Build options
# ---------------------------------------------------------------------------------------
option(ezli_BUILD_LOMEEXAMPLE "Build test my learning example(for dev purpose only)" ON)
option(ezli_ENABLE_HINTS "Enable hints feature(it's just comment for UNIX API)" ON)


# ---------------------------------------------------------------------------------------
# Start to build library
# ---------------------------------------------------------------------------------------
project(ezli LANGUAGES CXX)
include(GNUInstallDirs)

add_library(helper INTERFACE)
add_library(${PROJECT_NAME}::helper ALIAS helper)

add_library(hints INTERFACE)
add_library(${PROJECT_NAME}::hints ALIAS hints)

target_include_directories(helper
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(hints
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# ---------------------------------------------------------------------------------------
# Start to build example-test(for dev purpose only)
# ---------------------------------------------------------------------------------------

if (ezli_BUILD_LOMEEXAMPLE)
    add_subdirectory(lome_example)
endif()

# ---------------------------------------------------------------------------------------
# Install
# ---------------------------------------------------------------------------------------

list(APPEND lib_name helper)

if (ezli_ENABLE_HINTS)
    list(APPEND lib_name hints)
endif()

install(
    TARGETS ${lib_name} EXPORT ${PROJECT_NAME}-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT ${PROJECT_NAME}-config
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}-config-targets.cmake
)

include(CMakePackageConfigHelpers)
configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in" 
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})

if (NOT ezli_ENABLE_HINTS)
    file(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/include/ezli/hints)
endif()

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp*" PATTERN "*.inl*" PATTERN "*.h*"
)