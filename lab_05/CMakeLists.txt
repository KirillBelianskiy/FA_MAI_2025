project(lab_05)

add_executable(lab_05_run src/main.c src/functions.c)

add_executable(lab_05_tests tests/test_cases.cpp src/functions.c)

target_link_libraries(lab_05_tests PRIVATE gtest gtest_main)