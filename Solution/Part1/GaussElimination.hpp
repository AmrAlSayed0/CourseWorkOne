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
	float _matrix[3][4], result[3];
	GaussElimination(int d);
	void SetSource();
	void Apply_Pivotisation();
	void Print_Matrix();
	void back_substitution();
	void Perform_Elimination();
	virtual ~GaussElimination();
};

#endif /* GAUSSELIMINATION_H_ */
