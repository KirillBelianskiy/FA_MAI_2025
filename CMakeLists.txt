cmake_minimum_required(VERSION 3.23)
project(fundamental_algorithms)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(lab_01)
add_subdirectory(lab_02)
add_subdirectory(lab_03)
add_subdirectory(lab_04)
add_subdirectory(lab_05)
add_subdirectory(lab_06)
add_subdirectory(lab_07)
add_subdirectory(lab_08)

add_subdirectory(lab_11)
add_subdirectory(lab_12)
add_subdirectory(lab_16)