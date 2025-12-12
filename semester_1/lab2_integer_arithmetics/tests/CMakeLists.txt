cmake_minimum_required(VERSION 3.10)
project(lab2_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main lib
add_library(task_lib task.cpp)
target_include_directories(task_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ===== GOOGLE TEST =====
# sudo apt-get install libgtest-dev
find_package(GTest REQUIRED)
add_executable(gtest gtest/google_test.cpp)
# link our executable test file with libs (task3 and gtest)
target_link_libraries(gtest task_lib GTest::gtest GTest::gtest_main)

# ===== BOOST TEST =====
# sudo apt-get install libboost-test-dev
find_package(Boost 1.71 REQUIRED COMPONENTS unit_test_framework)
add_executable(boost btest/boost_test.cpp)
target_link_libraries(boost task_lib Boost::unit_test_framework)

# ===== TESTS =====
enable_testing()
add_test(NAME GoogleTests COMMAND gtest)
add_test(NAME BoostTests COMMAND boost)

# add_executable(task task.cpp)
# add_executable(dop_task1 dop_task1.cpp)
# add_executable(dop_task2 dop_task2.cpp)
# add_custom_target(tasks DEPENDS task dop_task1 dop_task2)