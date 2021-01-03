/*
 * GaussSeidel.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Ahmed Samir
 */
#include "GaussSeidel.hpp"
#include <iostream>
using namespace std;
namespace Solution::Part1
{
    GaussSeidel::GaussSeidel ( int nomOfIt )
        : Solver ()
    {
        this->numberOfIteration = nomOfIt;
    }
    /*
     * public function to apply Gauss seidel method for the given matrix
     * @number of iteration
     * */
    float * GaussSeidel::Apply ()
    {
        this->result = new float[this->nd];
        //int values with zeros
        for ( int i = 0; i < this->nd; i++ )
        {
            this->result[ i ] = 0;
        }
        for ( int i = 0; i < this->numberOfIteration; i++ )
        {
            this->Seidel_Core ();
            if ( this->debug_mode )
            {
                cout << "iteration " << i << endl;
                for ( int ii = 0; ii < this->nd; ii++ )
                {
                    cout << this->result[ ii ] << endl;
                }
            }
        }
        // returning our updated solution
        return this->result;
    }
    /*
     * seidel methode core
     * */
    void GaussSeidel::Seidel_Core ()
    {

        // for loop for 3 times as to calculate x, y , z
        for ( int j = 0; j < this->nd; j++ )
        {
            // temp variable d to store b[j]
            float d = this->_matrix[ j ][ this->nd ];

            // to calculate respective xi, yi, zi
            for ( int i = 0; i < this->nd; i++ )
            {
                if ( j != i )
                {
                    d -= this->_matrix[ j ][ i ] * this->result[ i ];
                }
            }
            // updating the value of our solution
            this->result[ j ] = d / this->_matrix[ j ][ j ];
        }
    }
}
