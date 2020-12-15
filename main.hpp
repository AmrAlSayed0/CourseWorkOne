#ifndef COURSEWORKONE_MAIN_HPP
#define COURSEWORKONE_MAIN_HPP
#include <string>
#include <vector>
#include "MatrixLib/Matrix.hpp"
#include "Solution/Part1/GaussElimination.hpp"
#include "Solution/Part3/NewtonInterpolation.hpp"
using float_type = float;
void present_part_1 ();
void present_part_3 ();
template < class T >
void read_x_and_y_values ( const std::string &path , std::vector < T > &xValues , std::vector < T > &yValues );
template < class T >
T parse_string_to_float_type ( std::string &toParse );
template <>
float parse_string_to_float_type ( std::string &toParse );
template <>
double parse_string_to_float_type ( std::string &toParse );
template <>
long double parse_string_to_float_type ( std::string &toParse );
template < class T >
void print_matrix ( Core::Matrix < T > &mat );
template < class T >
void print_prediction_result ( const std::vector < T > &xValues , const std::vector < T > &yValues , const std::vector < T > &predictedYValues , const std::string &outputFilePath );
template < class T >
void print_coefficients ( std::vector < T > coefficients , const std::string &filePath );
template < class T >
std::string get_padded_float_format ();
template <>
std::string get_padded_float_format < float > ();
template <>
std::string get_padded_float_format < double > ();
template <>
std::string get_padded_float_format < long double > ();
template < class T >
std::string get_unpaded_float_format ();
template <>
std::string get_unpaded_float_format < float > ();
template <>
std::string get_unpaded_float_format < double > ();
template <>
std::string get_unpaded_float_format < long double > ();
template < typename ... Args >
std::string string_format ( const std::string &format , Args ... args );
#endif //COURSEWORKONE_MAIN_HPP
