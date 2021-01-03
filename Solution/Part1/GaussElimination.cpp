/*
 * GaussElimination.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Ahmed Samir
 */
#include "GaussElimination.hpp"
#include <iostream>
using namespace std;
namespace Solution::Part1
{
    /*
     * Apply the core logic of gauss elimination method
     * */
    float * GaussElimination::Elimination_Core ()
    {
        this->Apply_Pivotisation ();
        if ( this->debug_mode )
        {
            cout << "\n=========================Pivotisation result=========================\n";
            this->Print_Matrix ( this->_matrix );
        }
        this->Perform_Elimination ();
        if ( this->debug_mode )
        {
            cout << "\n============================Perform_Elimination======================\n";
            this->Print_Matrix ( this->_matrix );
        }
        this->back_substitution ();
        return this->result;
    }
    /*
     * public function to Apply Guess elimination method
     * */
    float * GaussElimination::Apply ()
    {
        return this->Elimination_Core ();
    }
    /*
     * Apply the Pivotisation phase of the gauss elimination method
     * */
    void GaussElimination::Apply_Pivotisation ()
    {
        for ( int i = 0; i < nd; i++ )
        {
            for ( int k = i + 1; k < nd; k++ )
            {
                if ( abs ( _matrix[ i ][ i ] ) < abs ( _matrix[ k ][ i ] ) )
                {
                    for ( int j = 0; j <= nd; j++ )
                    {
                        float temp = _matrix[ i ][ j ];
                        _matrix[ i ][ j ] = _matrix[ k ][ j ];
                        _matrix[ k ][ j ] = temp;
                    }
                }
            }
        }
    }
    /*
     * Apply the elimination phase of Gauss elimination method
     * */
    void GaussElimination::Perform_Elimination ()
    {
        for ( int i = 0; i < nd - 1; i++ )
        {
            for ( int k = i + 1; k < nd; k++ )
            {
                double t = _matrix[ k ][ i ] / _matrix[ i ][ i ];
                if ( this->debug_mode )
                {
                    cout << "\nmultiply row " << k << " by row " << i << " *" << t << "\n";
                }
                for ( int j = 0; j <= nd; j++ )
                {
                    _matrix[ k ][ j ] = _matrix[ k ][ j ] - t * _matrix[ i ][ j ];
                } //make the elements below the pivot elements equal to zero or elimnate the variables

                //			this->Print_Matrix(this->_matrix);

            }
        }
    }
    /*
     * Apply the back_substitution phase of the Gauss elimination method
     * */
    void GaussElimination::back_substitution ()
    {
        for ( int i = nd - 1; i >= 0; i-- )
        { //x is an array whose values correspond to the values of x,y,z..
            result[ i ] = _matrix[ i ][ nd ]; //make the variable to be calculated equal to the rhs of the last equation
            for ( int j = i + 1; j < nd; j++ )
            {
                if ( j != i )
                { //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
                    result[ i ] = result[ i ] - _matrix[ i ][ j ] * result[ j ];
                }
            }
            result[ i ] = result[ i ] / _matrix[ i ][ i ]; //now finally divide the rhs by the coefficient of the variable to be calculated
        }
    }
}
