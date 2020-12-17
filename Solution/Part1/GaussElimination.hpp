/*
 * GaussElimination.h
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */

#ifndef GAUSSELIMINATION_H_
#define GAUSSELIMINATION_H_

class GaussElimination {
public:
	int nd = 3;
	float** _matrix;
	float* result;
	bool valid_solution =false;
	GaussElimination(int d);
	void SetSource();
	void Apply_Pivotisation();
	void Print_Matrix(float** m);
	void back_substitution();
	void Perform_Elimination();
	float** lower();
	int determinantOfMatrix(float** f);
	virtual ~GaussElimination();
};

#endif /* GAUSSELIMINATION_H_ */
