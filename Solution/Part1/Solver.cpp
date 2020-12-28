#include<iostream>
#include <bits/stdc++.h>

#include "Solver.hpp"
using namespace std;

Solver::Solver(){
	this->_matrix = NULL ;
	this->result = NULL ;
}

Solver::~Solver() {
	delete this->_matrix;
}



/**
 * input the elements of array
 * */
void Solver::SetSource() {

	cout
					<< "\nEnter the elements of the matrix row by row space separated:\n";

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
void Solver::ImportSource(float **f,int len) {

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

/*
 * Apply the lower triangular matrix
 * */

float** Solver::lower() {
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
/*
 * Calculate the determinant Of any given Matrix
 * */

int Solver::determinantOfMatrix(float **mat) {
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

/*
 * Print a given matrix content
 * */
void Solver::Print_Matrix(float **m) {
	cout << "----------------------------------\n";
	for (int i = 0; i < nd; i++) {
		for (int j = 0; j <= nd; j++)
			cout << m[i][j] << setw(16);
		cout << "\n";
	}
	cout << "----------------------------------\n";
}


