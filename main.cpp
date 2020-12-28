#include <memory>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Solution/Part1/GaussSeidel.hpp"
#include "Solution/Part1/GaussElimination.hpp" 
#include "Solution/Part3/CubicSplineInterpolator.hpp"
#include "Solution/Part3/Helpers.hpp"
#include "Solution/Part3/NewtonInterpolator.hpp"
#include "main.hpp"
int main ()
{
    presentPart1 ();
    presentPart3 ();
    return 0;
}
void presentPart1 ()
{
    std::cout << std::fixed;
    std::cout << std::setprecision ( 2 );
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


}
void presentPart3 ()
{
    std::vector < float_type > d1Xs;
    std::vector < float_type > d1Ys;
    std::vector < float_type > d2Xs;
    std::vector < float_type > d2Ys;
    /** Reading both data sets */
    readXAndYValues < float_type > ( R"(..\datasets\part_3\3_dataset_1.csv)" , d1Xs , d1Ys );
    readXAndYValues < float_type > ( R"(..\datasets\part_3\3_dataset_2.csv)" , d2Xs , d2Ys );
    /** Get test X values based on the original x values. Will divide the range into 500 numbers. */
    std::vector < float_type > testD1Xs = getTestXs ( d1Xs );
    std::vector < float_type > testD2Xs = getTestXs ( d2Xs );
    /** Doing Newton interpolation first */
    auto d1NewtonInterpolation = Solution::Part3::NewtonInterpolator < float_type > ();
    /** Fitting the data */
    d1NewtonInterpolation.fit ( d1Xs , d1Ys );
    /** Interpolating the same X values to compare the result */
    auto d1NewtPredYs = d1NewtonInterpolation.interpolate ( d1Xs );
    auto d1NewtPredTestYs = d1NewtonInterpolation.interpolate ( testD1Xs );
    /** Printing the prediction and the coefficients to file */
    printPredictionResult ( d1Xs , d1Ys , d1NewtPredYs , R"(..\datasets\part_3\Newt_Pred_Points_1.csv)" );
    printPredictionResult ( testD1Xs , d1NewtPredTestYs , d1NewtPredTestYs , R"(..\datasets\part_3\Newt_Test_Pred_Points_1.csv)" );
    printCoefficients ( d1NewtonInterpolation.getCoefficients () , R"(..\datasets\part_3\Newt_Coeff_1.csv)" );
    /** Repeating Newton for the second data set */
    auto d2NewtonInterpolation = Solution::Part3::NewtonInterpolator < float_type > ();
    d2NewtonInterpolation.fit ( d2Xs , d2Ys );
    auto d2NewtPredYs = d2NewtonInterpolation.interpolate ( d2Xs );
    auto d2NewtPredTestYs = d2NewtonInterpolation.interpolate ( testD2Xs );
    printPredictionResult ( d2Xs , d2Ys , d2NewtPredYs , R"(..\datasets\part_3\Newt_Pred_Points_2.csv)" );
    printPredictionResult ( testD2Xs , d2NewtPredTestYs , d2NewtPredTestYs , R"(..\datasets\part_3\Newt_Test_Pred_Points_2.csv)" );
    printCoefficients ( d2NewtonInterpolation.getCoefficients () , R"(..\datasets\part_3\Newt_Coeff_2.csv)" );
    /** Now using the cubic spline */
    auto d1CubicSplineInterpolation = Solution::Part3::CubicSplineInterpolator < float_type > ();
    /** Fitting the data */
    d1CubicSplineInterpolation.fit ( d1Xs , d1Ys );
    /** Interpolating the same X values to compare the result */
    auto d1CuPredYs = d1CubicSplineInterpolation.interpolate ( d1Xs );
    auto d1CuPredTestYs = d1CubicSplineInterpolation.interpolate ( testD1Xs );
    /** Printing the prediction and the coefficients to file */
    printPredictionResult ( d1Xs , d1Ys , d1CuPredYs , R"(..\datasets\part_3\Cube_Pred_Points_1.csv)" );
    printPredictionResult ( testD1Xs , d1CuPredTestYs , d1CuPredTestYs , R"(..\datasets\part_3\Cube_Test_Pred_Points_1.csv)" );
    printCoefficients ( d1CubicSplineInterpolation.getCoefficients () , R"(..\datasets\part_3\Cube_Coeff_1.csv)" );
    /** Repeating Cubic for the second data set */
    auto d2CubicSplineInterpolation = Solution::Part3::CubicSplineInterpolator < float_type > ();
    d2CubicSplineInterpolation.fit ( d2Xs , d2Ys );
    auto d2CuPredYs = d2CubicSplineInterpolation.interpolate ( d2Xs );
    auto d2CuPredTestYs = d2CubicSplineInterpolation.interpolate ( testD2Xs );
    printPredictionResult ( d2Xs , d2Ys , d2CuPredYs , R"(..\datasets\part_3\Cube_Pred_Points_2.csv)" );
    printPredictionResult ( testD2Xs , d2CuPredTestYs , d2CuPredTestYs , R"(..\datasets\part_3\Cube_Test_Pred_Points_2.csv)" );
    printCoefficients ( d2CubicSplineInterpolation.getCoefficients () , R"(..\datasets\part_3\Cube_Coeff_2.csv)" );
    std::system ( R"(python.exe "..\Plot.py")" );
}


