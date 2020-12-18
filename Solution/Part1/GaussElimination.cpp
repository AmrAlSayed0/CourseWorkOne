/*
 * GaussElimination.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */
#include<iostream>
#include <iomanip>
#include <cmath>
#include "GaussElimination.hpp"
using namespace std;
GaussElimination::GaussElimination ( int d )
{
    // TODO Auto-generated constructor stub
    this->nd = d;
    this->result = new float[d];
    this->_matrix = new float * [this->nd];
}
GaussElimination::~GaussElimination ()
{
    delete this->_matrix;
}
/**
 * input the elements of array
 * */
void GaussElimination::SetSource() {

	int determinant,determinant2 ;
	for (int i = 0; i < this->nd; i++) {

		cout << "enter row number " << i  << endl;

		this->_matrix[i] = new float[this->nd + 1];

		for (int j = 0; j <= nd; j++)
			cin >> _matrix[i][j];
	}
	float **tmp = this->lower();

	determinant = this->determinantOfMatrix(tmp);

	//cout << determinant << endl;
	int fixed_number = 3;
	for (int i = 0; i < this->nd; i++) {
		for (int j = 0; j < this->nd; j++) {
			tmp[i][j] = tmp[i][j]*fixed_number;
		}
	}
	determinant2 = this->determinantOfMatrix(tmp);
	//cout << determinant2 << endl;

	this->valid_solution = (determinant == determinant2);


}

void GaussElimination::Apply_Pivotisation() {
	for (int i = 0; i < nd; i++)
		for (int k = i + 1; k < nd; k++)
			if (abs(_matrix[i][i]) < abs(_matrix[k][i]))
				for (int j = 0; j <= nd; j++) {
					float temp = _matrix[i][j];
					_matrix[i][j] = _matrix[k][j];
					_matrix[k][j] = temp;
				}
}
void GaussElimination::Print_Matrix(float **m) {
	cout << "----------------------------------\n";
	for (int i = 0; i < nd; i++) {
		for (int j = 0; j <= nd; j++)
			cout << m[i][j] << setw(16);
		cout << "\n";
	}
	cout << "----------------------------------\n";
}

void GaussElimination::Perform_Elimination() {

	for (int i = 0; i < nd - 1; i++) {
		for (int k = i + 1; k < nd; k++) {
			double t = _matrix[k][i] / _matrix[i][i];
			cout << "\n";
			cout << "multiply row " << k << " by row " << i << " *" << t
					<< "\n";
			for (int j = 0; j <= nd; j++)
				_matrix[k][j] = _matrix[k][j] - t * _matrix[i][j]; //make the elements below the pivot elements equal to zero or elimnate the variables

//			this->Print_Matrix(this->_matrix);

		}
	}
}

void GaussElimination::back_substitution() {
	for (int i = nd - 1; i >= 0; i--) { //x is an array whose values correspond to the values of x,y,z..
		result[i] = _matrix[i][nd]; //make the variable to be calculated equal to the rhs of the last equation
		for (int j = i + 1; j < nd; j++)
			if (j != i) //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
				result[i] = result[i] - _matrix[i][j] * result[j];
		result[i] = result[i] / _matrix[i][i]; //now finally divide the rhs by the coefficient of the variable to be calculated
	}
}

float** GaussElimination::lower()
{
    float ** omatrix;
    omatrix = new float * [this->nd];
    for ( int i = 0; i < this->nd; i++ )
    {
        omatrix[ i ] = new float[this->nd];
        for ( int j = 0; j < this->nd; j++ )
        {
            if ( i < j )
            {
                omatrix[ i ][ j ] = 0;
            }
            else
            {
                omatrix[ i ][ j ] = this->_matrix[ i ][ j ];
            }
        }
	}
	return omatrix;
}

int GaussElimination::determinantOfMatrix(float **mat) {
	float num1, num2, det = 1, total = 1; // Initialize result
	int index;
	// temporary array for storing row
	float temp[this->nd + 1];

	// loop for traversing the diagonal elements
	for (int i = 0; i < this->nd; i++) {
		index = i; // initialize the index

		// finding the index which has non zero value
		while (mat[index][i] == 0 && index < this->nd) {
			index++;
		}
		if (index == this->nd) // if there is non zero element
				{
			// the determinat of matrix as zero
			continue;
		}
		if (index != i) {
			// loop for swaping the diagonal element row and
			// index row
			for (int j = 0; j < this->nd; j++) {
				float t = mat[index][j];
				mat[index][j] = mat[i][j];
				mat[i][j] = t;
			}
			// determinant sign changes when we shift rows
			// go through determinant properties
			det = det * pow(-1, index - i);
		}

		// storing the values of diagonal row elements
		for (int j = 0; j < this->nd; j++) {
			temp[j] = mat[i][j];
		}
		// traversing every row below the diagonal element
		for (int j = i + 1; j < this->nd; j++) {
			num1 = temp[i]; // value of diagonal element
			num2 = mat[j][i]; // value of next row element

			// traversing every column of row
			// and multiplying to every row
			for (int k = 0; k < this->nd; k++) {
				// multiplying to make the diagonal
				// element and next row element equal
				mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);
			}
			total = total * num1; // Det(kA)=kDet(A);
		}
	}

	// mulitplying the diagonal elements to get determinant
	for (int i = 0; i < this->nd; i++) {
		det = det * mat[i][i];
	}
	return (det / total); // Det(kA)/k=Det(A);
}

