project(lab_01)

add_executable(lab_01_run src/main.c src/functions.c)

add_executable(lab_01_tests tests/test_cases.cpp src/functions.c)

target_link_libraries(lab_01_tests PRIVATE gtest gtest_main)