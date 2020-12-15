/*
 * GaussElimination_test
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */


#include<iostream>
#include <vector>
#include <string>
#include <sstream>
#include "GaussElimination.h"
using namespace std;

int main() {

	int n;


	cout << "\nEnter the no. of equations\n";
	cin >> n;                //input the no. of equations

	GaussElimination GL(n);

	cout << "\nEnter the elements of the matrix row by row space separated:\n";
	GL.SetSource();



	GL.Apply_Pivotisation();

	GL.Print_Matrix();

	cout << "\n==================================================\n";

	GL.Perform_Elimination();


	cout << "\n==================================================\n";

	GL.back_substitution();


	cout << "\nThe values of the variables are as follows:\n";
	for (int i = 0; i < GL.nd; i++)
		cout << GL.result[i] << endl;            // Print the values of x, y,z,....
	return 0;
}
