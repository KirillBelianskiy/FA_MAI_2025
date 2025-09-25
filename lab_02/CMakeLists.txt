project(lab_02)

add_executable(lab_02_run src/main.c src/functions.c)

add_executable(lab_02_tests tests/test_cases.cpp src/functions.c)

target_link_libraries(lab_02_tests PRIVATE gtest gtest_main)