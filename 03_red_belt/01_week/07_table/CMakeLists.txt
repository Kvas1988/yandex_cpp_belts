cmake_minimum_required(VERSION 3.1) # ???
set (CMAKE_CXX_STANDARD 11)

project(belt)

include_directories(../../) # test_runner.h

add_executable(hw table.cpp)

