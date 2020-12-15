/*
 * GaussElimination.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */
#include<iostream>
#include "GaussElimination.h"
using namespace std;
GaussElimination::GaussElimination(int d) {
	// TODO Auto-generated constructor stub
	this->nd = d;
}

GaussElimination::~GaussElimination() {
	delete this->_matrix;
}
/**
 * input the elements of array
 * */
void GaussElimination::SetSource() {

	for (int i = 0; i < this->nd; i++)
		for (int j = 0; j <= nd; j++)
			cin >> _matrix[i][j];

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
void GaussElimination::Print_Matrix() {
	for (int i = 0; i < nd; i++) {
		for (int j = 0; j <= nd; j++)
			cout << _matrix[i][j] << "\t\t\t";
		cout << "\n";
	}
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

			this->Print_Matrix();

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

