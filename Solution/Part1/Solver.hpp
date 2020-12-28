#ifndef Solver_H_
#define Solver_H_

#include<iostream>

using namespace std;

class Solver {
private:
	float** lower();

protected:
	int determinantOfMatrix(float **f);



public:
	void Print_Matrix(float **m);

	Solver();

	int nd = 3;
	float **_matrix ;
	float *result;
	bool valid_solution = false, debug_mode = false;
	void ImportSource(float **f, int len);
	void SetSource();

	virtual ~Solver();

	virtual float* Apply(){ cout <<"parent" ;} ;

};

#endif /* Solver_H_ */
