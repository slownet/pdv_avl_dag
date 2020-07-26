cmake_minimum_required(VERSION 3.5.1)
project(PDV_DAG_AVL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp -march=native -pthread")

add_executable(dag_avl main_dag_avl.cpp dag_avl.cpp dag_avl.h)

