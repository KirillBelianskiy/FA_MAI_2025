project(lab_07)

add_executable(lab_07_run src/main.c src/functions.c)

add_executable(lab_07_tests tests/test_cases.cpp src/functions.c)

target_link_libraries(lab_07_tests PRIVATE gtest gtest_main)