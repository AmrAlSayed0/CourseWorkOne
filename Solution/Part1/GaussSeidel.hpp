/*
 * GaussSeidel.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Ahmed Samir
 */
#ifndef COURSEWORKONE_GAUSSSEIDEL_HPP
#define COURSEWORKONE_GAUSSSEIDEL_HPP
#include "Solver.hpp"
namespace Solution::Part1
{
    class GaussSeidel
        : public Solution::Part1::Solver
    {
    private:
        int numberOfIteration;
        void Seidel_Core ();
    public:
        GaussSeidel ( int numberOfIteration );
        float * Apply ();
    };
}
#endif //COURSEWORKONE_GAUSSSEIDEL_HPP
