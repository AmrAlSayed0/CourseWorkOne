cmake_minimum_required(VERSION 3.16)
project(CourseWorkOne)

set(CMAKE_CXX_STANDARD 17)

add_executable(CourseWorkOne Solution/Part1/Gauss.cpp Solution/Part1/Gauss.h Solution/Part2/cf_regression.cpp Solution/Part2/cf_regression.h Solution/Part3/Interpolator.cpp Solution/Part3/Interpolator.hpp Solution/Part3/NewtonInterpolator.cpp Solution/Part3/NewtonInterpolator.hpp Solution/Part3/CubicSplineInterpolator.cpp Solution/Part3/CubicSplineInterpolator.hpp Solution/Part3/Helpers.hpp main.cpp main.hpp)
