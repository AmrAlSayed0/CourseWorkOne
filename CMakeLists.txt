cmake_minimum_required(VERSION 3.16)
project(CourseWorkOne)

set(CMAKE_CXX_STANDARD 17)

add_executable(CourseWorkOne Solution/Part1/Gauss.cpp Solution/Part1/Gauss.h Solution/Part3/CubicSplineInterpolation.cpp Solution/Part3/CubicSplineInterpolation.hpp Solution/Part3/Helpers.hpp Solution/Part3/NewtonInterpolation.cpp Solution/Part3/NewtonInterpolation.hpp main.cpp main.hpp)
