cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project (red_belt)

include_directories(./)

add_executable(w1ex01 01_week/01_max_element_if/max_element_if.cpp)
add_executable(w1ex02 01_week/02_log/log.cpp)

add_executable(w2ex01 02_week/01_sort_students/sort_students.cpp)
add_executable(w2ex02 02_week/02_learner/learner.cpp)
add_executable(w2ex03 02_week/03_express/express.cpp)

add_executable(w3ex01 03_week/01_object_pool/object_pool.cpp)
add_executable(w3ex02 03_week/02_swap_sort_copy/swap_sort_copy.cpp)
add_executable(w3ex03 03_week/03_simple_vector/simple_vector.cpp)
add_executable(w3ex04 03_week/04_linked_list/linked_list.cpp)

add_executable(w4ex01 04_week/01_athletes/athletes.cpp)
add_executable(w4ex02 04_week/02_stack_vector/stack_vector.cpp)
add_executable(w4_ex03 04_week/03_translator/translator.cpp)