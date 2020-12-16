#include <memory>
#include <iostream>
#include <vector>
#include "Solution/Part1/GaussElimination.hpp"
#include "Solution/Part3/CubicSplineInterpolation.hpp"
#include "Solution/Part3/Helpers.hpp"
#include "Solution/Part3/NewtonInterpolation.hpp"
#include "main.hpp"
int main ()
{
    //present_part_1 ();
    present_part_3 ();
    return 0;
}
void present_part_1 ()
{
    int n;
    std::cout << "\nEnter the no. of equations\n";
    std::cin >> n;                //input the no. of equations

    GaussElimination GL ( n );
    std::cout << "\nEnter the elements of the matrix row by row space separated:\n";
    GL.SetSource ();
    GL.Apply_Pivotisation ();
    GL.Print_Matrix ();
    std::cout << "\n==================================================\n";
    GL.Perform_Elimination ();
    std::cout << "\n==================================================\n";
    GL.back_substitution ();
    std::cout << "\nThe values of the variables are as follows:\n";
    for ( int i = 0; i < GL.nd; i++ )
    {
        std::cout << GL.result[ i ] << std::endl; // Print the values of x, y,z,....
    }
}
void present_part_3 ()
{
    std::vector < float_type > dataset1XValues;
    std::vector < float_type > dataset1YValues;
    std::vector < float_type > dataset2XValues;
    std::vector < float_type > dataset2YValues;
    //std::vector < float_type > dataset1XValues = { 3 , 4.5 , 7 , 9 };
    //std::vector < float_type > dataset1YValues = { 2.5 , 1 , 2.5 , 0.5 };
    //std::vector < float_type > dataset2XValues = { 3 , 4.5 , 7 , 9 };
    //std::vector < float_type > dataset2YValues = { 2.5 , 1 , 2.5 , 0.5 };
    //Reading both data sets
    read_x_and_y_values < float_type > ( R"(..\datasets\part_3\3_dataset_1.csv)" , dataset1XValues , dataset1YValues );
    read_x_and_y_values < float_type > ( R"(..\datasets\part_3\3_dataset_2.csv)" , dataset2XValues , dataset2YValues );
    //Doing Newtown interpolation first
    auto dataset1NewtonInterpolation = Solution::Part3::NewtonInterpolation < float_type > ();
    //Fitting the data
    dataset1NewtonInterpolation.fit ( dataset1XValues , dataset1YValues );
    //Interpolating the same X values to compare the result
    auto dataset1NewtonInterpolationResult = dataset1NewtonInterpolation.interpolate ( dataset1XValues );
    //Printing the prediction and the coefficients to file
    print_prediction_result ( dataset1XValues , dataset1YValues , dataset1NewtonInterpolationResult , R"(..\datasets\part_3\3_newt_points_1.csv)" );
    print_coefficients ( dataset1NewtonInterpolation.getCoefficients () , R"(..\datasets\part_3\3_newt_coeff_1.csv)" );
    //Repeating Newton for the second data set
    auto dataset2NewtonInterpolation = Solution::Part3::NewtonInterpolation < float_type > ();
    dataset2NewtonInterpolation.fit ( dataset2XValues , dataset2YValues );
    auto dataset2NewtonInterpolationResult = dataset2NewtonInterpolation.interpolate ( dataset2XValues );
    print_prediction_result ( dataset2XValues , dataset2YValues , dataset2NewtonInterpolationResult , R"(..\datasets\part_3\3_newt_points_2.csv)" );
    print_coefficients ( dataset2NewtonInterpolation.getCoefficients () , R"(..\datasets\part_3\3_newt_coeff_2.csv)" );
    //Now using the cubic spline
    auto dataset1CubicSplineInterpolation = Solution::Part3::CubicSplineInterpolation < float_type > ();
    //Fitting the data
    dataset1CubicSplineInterpolation.fit ( dataset1XValues , dataset1YValues );
    //Interpolating the same X values to compare the result
    auto dataset1CubicSplineInterpolationResult = dataset1CubicSplineInterpolation.interpolate ( dataset1XValues );
    //Printing the prediction and the coefficients to file
    print_prediction_result ( dataset1XValues , dataset1YValues , dataset1CubicSplineInterpolationResult , R"(..\datasets\part_3\3_cube_points_1.csv)" );
    print_coefficients ( dataset1CubicSplineInterpolation.getCoefficients () , R"(..\datasets\part_3\3_cube_coeff_1.csv)" );
    //Repeating Cubic for the second data set
    auto dataset2CubicSplineInterpolation = Solution::Part3::CubicSplineInterpolation < float_type > ();
    dataset2CubicSplineInterpolation.fit ( dataset2XValues , dataset2YValues );
    auto dataset2CubicSplineInterpolationResult = dataset2CubicSplineInterpolation.interpolate ( dataset2XValues );
    print_prediction_result ( dataset2XValues , dataset2YValues , dataset2CubicSplineInterpolationResult , R"(..\datasets\part_3\3_cube_points_2.csv)" );
    print_coefficients ( dataset2CubicSplineInterpolation.getCoefficients () , R"(..\datasets\part_3\3_cube_coeff_2.csv)" );
}

