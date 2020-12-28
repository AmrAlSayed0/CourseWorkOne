/*
 * Gauss_test
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */

#include<iostream>
#include <vector>
#include <string>
#include <sstream>

#include "GaussSeidel.hpp"
#include "GaussElimination.hpp"

using namespace std;

int main() {

	int option = 0, debug = 0;

	Solver *S;

	cout << "enter 1 for debug " << endl;
	cin >> debug;

	//cout << GL.valid_solution << endl;

	cout << "enter 1 for GaussElimination or 2 for seidel" << endl;
	cin >> option;

	if (option == 1) {

		GaussElimination g;
		S = &g;
		if (debug == 1) {
			S->debug_mode = true;
		}
		S->SetSource();
		S->Apply();

	} else {

		GaussSeidel g(30);
		S = &g;
		if (debug == 1) {
			S->debug_mode = true;
		}
		S->SetSource();
		S->Apply();
	}

	cout << "\nThe values of the variables are as follows:\n";
	for (int i = 0; i < S->nd; i++)
		cout << S->result[i] << endl;         // Print the values of x, y,z,....

	return 0;
}
