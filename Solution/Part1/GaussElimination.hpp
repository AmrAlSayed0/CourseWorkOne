/*
 * GaussElimination.h
 *
 *  Created on: Dec 13, 2020
 *      Author: asamir
 */

#ifndef GAUSSELIMINATION_HPP_
#define GAUSSELIMINATION_HPP_

#include "Solver.hpp"

class GaussElimination : public Solver {

private:


	void Apply_Pivotisation();

	void back_substitution();
	void Perform_Elimination();

	float* Elimination_Core();
public :

	float* Apply();


};

#endif /* GAUSSELIMINATION_HPP_ */
