/*
 * GaussElimination.h
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */

#ifndef GAUSS_H_
#define GAUSS_H_

class Gauss {
public:
	int nd = 3;
	float **_matrix;
	float *result;
	bool valid_solution = false, debug_mode = false;

	Gauss();

	void SetSource();
	void ImportSource(float **f,int len);

	float** lower();
	int determinantOfMatrix(float **f);

	void Apply_Pivotisation();
	void Print_Matrix(float **m);
	void back_substitution();
	void Perform_Elimination();

	float* Apply_Elimination();
	float* Elimination_Core();

	float* ApplySeidel(int interation);
	void Seidel_Core();

	virtual ~Gauss();
};

#endif /* GAUSS_H_ */
