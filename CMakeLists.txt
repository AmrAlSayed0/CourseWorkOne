cmake_minimum_required(VERSION 3.16)
project(CourseWorkOne)

set(CMAKE_CXX_STANDARD 14)

add_executable(CourseWorkOne main.hpp main.cpp Solution/Part1/GaussElimination.hpp Solution/Part1/GaussElimination.cpp MatrixLib/Matrix.hpp MatrixLib/Point.cpp MatrixLib/Point.hpp Solution/Part3/NewtonInterpolation.cpp Solution/Part3/NewtonInterpolation.hpp Solution/Part3/CubicSplineInterpolation.cpp Solution/Part3/CubicSplineInterpolation.hpp)
