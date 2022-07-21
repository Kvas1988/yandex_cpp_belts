cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_FLAGS "-O3")

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
add_executable(w4ex03 04_week/03_translator/translator.cpp)
add_executable(w4ex04 04_week/04_airport_counter/airport_counter.cpp)
add_executable(w4ex05 04_week/05_text_editor/text_editor.cpp)

#include_directories(04_week/06_web_server)
add_library(stats 04_week/06_web_server/stats.cpp)
add_executable(w4ex06 04_week/06_web_server/server_stats.cpp)
target_link_libraries(w4ex06 stats)