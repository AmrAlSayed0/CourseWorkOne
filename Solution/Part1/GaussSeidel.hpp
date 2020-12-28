/*
 * GaussElimination.h
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */

#ifndef GaussSeidel_H_
#define GaussSeidel_H_

#include "Solver.hpp"

class GaussSeidel :public Solver {

private:
	int numberOfIteration;

	void Seidel_Core();

public:

	GaussSeidel(int numberOfIteration);

	float* Apply();
};

#endif /* GaussSeidel_H_ */
