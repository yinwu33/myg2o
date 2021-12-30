cmake_minimum_required(VERSION 3.0)

project(myg2o)

include_directories(include)

find_package(Eigen3 REQUIRED)

add_subdirectory(src)