/*
 * Solver.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Ahmed Samir
 */
#ifndef COURSEWORKONE_SOLVER_HPP
#define COURSEWORKONE_SOLVER_HPP
#include<iostream>
using namespace std;
namespace Solution::Part1
{
    class Solver
    {
    private:
        float ** lower () const;
    protected:
        int determinantOfMatrix ( float ** f ) const;
    public:
        void Print_Matrix ( float ** m );
        Solver ();
        int nd = 3;
        float ** _matrix;
        float * result;
        bool valid_solution = false , debug_mode = false;
        void ImportSource ( float ** f , int len );
        void SetSource ();
        virtual ~Solver ();
        virtual float * Apply ()
        {
            cout << "parent";
        };
    };
}
#endif //COURSEWORKONE_SOLVER_HPP
