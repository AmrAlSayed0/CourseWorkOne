/*
 * Gauss.cpp
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */
#include <bits/stdc++.h>
#include<iostream>

#include "Gauss.h"
using namespace std;
Gauss::Gauss() {
	// TODO Auto-generated constructor stub
	this->result = NULL;
	this->_matrix = NULL;
}

Gauss::~Gauss() {
	delete this->_matrix;
}
/**
 * input the elements of array
 * */
void Gauss::SetSource() {
	int n = 0;

	cout << "\n Enter the no. of equations\n";
	cin >> n;                //input the no. of equations
	this->nd = n;

	float **f = new float*[this->nd];

	for (int i = 0; i < this->nd; i++) {

		cout << "\n Enter row number " << i << endl;

		f[i] = new float[this->nd + 1];

		for (int j = 0; j <= nd; j++)
			cin >> f[i][j];
	}

	this->ImportSource(f,n);

}
/**
 * input the elements of array
 * */
void Gauss::ImportSource(float **f,int len) {

	this->_matrix = f;
	this->nd = len ;
	this->result = new float[this->nd];

	int determinant, determinant2;

	float **tmp = this->lower();

	determinant = this->determinantOfMatrix(tmp);

	//cout << determinant << endl;
	int fixed_number = 3;
	for (int i = 0; i < this->nd; i++) {
		for (int j = 0; j < this->nd; j++) {
			tmp[i][j] = tmp[i][j] * fixed_number;
		}
	}

	determinant2 = this->determinantOfMatrix(tmp);
	//cout << determinant2 << endl;

	this->valid_solution = (determinant == determinant2);

}

float* Gauss::ApplySeidel(int interation) {

	this->result = new float[this->nd];
	//int values with zeros
	for (int i = 0; i < this->nd; i++) {
		this->result[i] = 0;
	}

	for (int i = 0; i < interation; i++) {
		this->Seidel_Core();
		if (this->debug_mode) {
			cout << "iteration " << i << endl;
			for (int ii = 0; ii < this->nd; ii++)
				cout << this->result[ii] << endl;
		}
	}
	// returning our updated solution
	return this->result;
}

float* Gauss::Elimination_Core() {

	this->Apply_Pivotisation();
	if (this->debug_mode) {
		cout
				<< "\n=========================Pivotisation result=========================\n";

		this->Print_Matrix(this->_matrix);

	}

	this->Perform_Elimination();
	if (this->debug_mode) {
		cout
				<< "\n============================Perform_Elimination======================\n";

		this->Print_Matrix(this->_matrix);
	}

	this->back_substitution();

	return this->result;
}
float* Gauss::Apply_Elimination() {
	return this->Elimination_Core();
}

void Gauss::Seidel_Core() {

	// for loop for 3 times as to calculate x, y , z
	for (int j = 0; j < this->nd; j++) {
		// temp variable d to store b[j]
		float d = this->_matrix[j][this->nd];

		// to calculate respective xi, yi, zi
		for (int i = 0; i < this->nd; i++)
			if (j != i)
				d -= this->_matrix[j][i] * this->result[i];
		// updating the value of our solution
		this->result[j] = d / this->_matrix[j][j];
	}

}

void Gauss::Apply_Pivotisation() {
	for (int i = 0; i < nd; i++)
		for (int k = i + 1; k < nd; k++)
			if (abs(_matrix[i][i]) < abs(_matrix[k][i]))
				for (int j = 0; j <= nd; j++) {
					float temp = _matrix[i][j];
					_matrix[i][j] = _matrix[k][j];
					_matrix[k][j] = temp;
				}
}
void Gauss::Print_Matrix(float **m) {
	cout << "----------------------------------\n";
	for (int i = 0; i < nd; i++) {
		for (int j = 0; j <= nd; j++)
			cout << m[i][j] << setw(16);
		cout << "\n";
	}
	cout << "----------------------------------\n";
}

void Gauss::Perform_Elimination() {

	for (int i = 0; i < nd - 1; i++) {
		for (int k = i + 1; k < nd; k++) {
			double t = _matrix[k][i] / _matrix[i][i];
			if(this->debug_mode)
			cout << "\nmultiply row " << k << " by row " << i << " *" << t
					<< "\n";
			for (int j = 0; j <= nd; j++)
				_matrix[k][j] = _matrix[k][j] - t * _matrix[i][j]; //make the elements below the pivot elements equal to zero or elimnate the variables

//			this->Print_Matrix(this->_matrix);

		}
	}
}

void Gauss::back_substitution() {
	for (int i = nd - 1; i >= 0; i--) { //x is an array whose values correspond to the values of x,y,z..
		result[i] = _matrix[i][nd]; //make the variable to be calculated equal to the rhs of the last equation
		for (int j = i + 1; j < nd; j++)
			if (j != i) //then subtract all the lhs values except the coefficient of the variable whose value                                   is being calculated
				result[i] = result[i] - _matrix[i][j] * result[j];
		result[i] = result[i] / _matrix[i][i]; //now finally divide the rhs by the coefficient of the variable to be calculated
	}
}

float** Gauss::lower() {
	float **omatrix = 0;
	omatrix = new float*[this->nd];

	for (int i = 0; i < this->nd; i++) {
		omatrix[i] = new float[this->nd];

		for (int j = 0; j < this->nd; j++) {
			if (i < j) {
				omatrix[i][j] = 0;
			} else
				omatrix[i][j] = this->_matrix[i][j];
		}
	}
	return omatrix;
}

int Gauss::determinantOfMatrix(float **mat) {
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

