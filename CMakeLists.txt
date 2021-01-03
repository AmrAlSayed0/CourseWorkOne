cmake_minimum_required(VERSION 3.16)
project(CourseWorkOne)

set(CMAKE_CXX_STANDARD 17)

add_executable(CourseWorkOne
        main.hpp
        main.cpp
        Solution/Part1/Solver.hpp
        Solution/Part1/Solver.cpp
        Solution/Part1/GaussElimination.hpp
        Solution/Part1/GaussElimination.cpp
        Solution/Part1/GaussSeidel.hpp
        Solution/Part1/GaussSeidel.cpp
        Solution/Part2/cf_regression.hpp
        Solution/Part2/cf_regression.cpp
        Solution/Part3/Helpers.hpp
        Solution/Part3/Interpolator.hpp
        Solution/Part3/Interpolator.cpp
        Solution/Part3/NewtonInterpolator.hpp
        Solution/Part3/NewtonInterpolator.cpp
        Solution/Part3/CubicSplineInterpolator.hpp
        Solution/Part3/CubicSplineInterpolator.cpp)
