cmake_minimum_required(VERSION 3.21)

# ----------------------------------------------------------------
#  Catch2 letöltése FetchContent-tel (nem kell külön telepíteni)
# ----------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.6.0
)
FetchContent_MakeAvailable(Catch2)

# ----------------------------------------------------------------
#  Teszt futtatható
# ----------------------------------------------------------------
add_executable(proglib_tests
    test_array_management.cpp
    test_binary_tree.cpp
    test_file_handling.cpp
)

target_link_libraries(proglib_tests
    PRIVATE
        proglib::proglib
        Catch2::Catch2WithMain
)

target_compile_features(proglib_tests PRIVATE cxx_std_20)

# Automatikus teszt-regisztráció CTest-be
include(Catch)
catch_discover_tests(proglib_tests)
