cmake_minimum_required(VERSION 3.21)

project(
    proglib
    VERSION 1.0.0
    DESCRIPTION "C++20 header-only általános célú könyvtár"
    LANGUAGES CXX
)

# ----------------------------------------------------------------
#  Opciók
# ----------------------------------------------------------------
option(PROGLIB_BUILD_TESTS "Tesztek fordítása" ON)

# ----------------------------------------------------------------
#  INTERFACE könyvtár (header-only → nincs .cpp, nincs fordítás)
# ----------------------------------------------------------------
add_library(proglib INTERFACE)
add_library(proglib::proglib ALIAS proglib)

target_include_directories(proglib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(proglib INTERFACE cxx_std_20)

# ----------------------------------------------------------------
#  Tesztek
# ----------------------------------------------------------------
if(PROGLIB_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------
#  Telepítési konfiguráció (find_package / FetchContent támogatás)
# ----------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    TARGETS proglib
    EXPORT proglibTargets
)

install(
    EXPORT proglibTargets
    FILE proglibTargets.cmake
    NAMESPACE proglib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/proglib
)

configure_package_config_file(
    cmake/proglibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/proglibConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/proglib
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/proglibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/proglibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/proglibConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/proglib
)
