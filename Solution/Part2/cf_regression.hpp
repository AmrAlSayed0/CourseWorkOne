/*
 * cf_regression.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Youssef Ansara
 */
#include <iostream>
#include <vector>
class cf_regression
{
public:
    static void fit_polyreg ( std::vector < float > x , std::vector < float > y , int order );
    static void predict_polyreg ( float x );
    static void fit_mlreg ( std::vector < std::vector < float>> x , std::vector < float > y , int order );
    static void predict_mlreg ( float x );
};
