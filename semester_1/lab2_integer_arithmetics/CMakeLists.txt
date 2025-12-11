cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# sudo apt-get install libgtest-dev
find_package(GTest REQUIRED)

add_library(task3_lib task3.cpp)
add_executable(gtest task3_tests.cpp)

# link our executable test file with libs (task3 and gtest)
target_link_libraries(gtest task3_lib GTest::gtest GTest::gtest_main)

enable_testing()

# add_executable(task3 task3.cpp)
# add_executable(dop_task1 dop_task1.cpp)
# add_executable(dop_task2 dop_task2.cpp)
# add_custom_target(tasks DEPENDS task3 dop_task1 dop_task2)