/*
 * GaussElimination.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Ahmed Samir
 */
#ifndef COURSEWORKONE_GAUSSELIMINATION_HPP
#define COURSEWORKONE_GAUSSELIMINATION_HPP
#include "Solver.hpp"
namespace Solution::Part1
{
    class GaussElimination
        : public Solver
    {
    private:
        void Apply_Pivotisation ();
        void back_substitution ();
        void Perform_Elimination ();
        float * Elimination_Core ();
    public :
        float * Apply ();
    };
}
#endif //COURSEWORKONE_GAUSSELIMINATION_HPP
