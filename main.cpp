#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>
#include "main.hpp"
int main ()
{
    present_part_1 ();
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
    read_x_and_y_values < float_type > ( R"(..\datasets\part_3\3_dataset_1.csv)" , dataset1XValues , dataset1YValues );
    read_x_and_y_values < float_type > ( R"(..\datasets\part_3\3_dataset_2.csv)" , dataset2XValues , dataset2YValues );
    auto dataset1NewtonInterpolation = Solution::Part3::NewtonInterpolation < float_type > ();
    dataset1NewtonInterpolation.fit ( dataset1XValues , dataset1YValues );
    auto dataset1NewtonInterpolationResult = dataset1NewtonInterpolation.interpolate ( dataset1XValues );
    print_prediction_result ( dataset1XValues , dataset1YValues , dataset1NewtonInterpolationResult , R"(..\datasets\part_3\3_newt_points_1.csv)" );
    print_coefficients ( dataset1NewtonInterpolation.getCoefficients () , R"(..\datasets\part_3\3_newt_coeff_1.csv)" );
    auto dataset2NewtonInterpolation = Solution::Part3::NewtonInterpolation < float_type > ();
    dataset2NewtonInterpolation.fit ( dataset2XValues , dataset2YValues );
    auto dataset2NewtonInterpolationResult = dataset2NewtonInterpolation.interpolate ( dataset2XValues );
    print_prediction_result ( dataset2XValues , dataset2YValues , dataset2NewtonInterpolationResult , R"(..\datasets\part_3\3_newt_points_2.csv)" );
    print_coefficients ( dataset2NewtonInterpolation.getCoefficients () , R"(..\datasets\part_3\3_newt_coeff_2.csv)" );
}
template < class T >
void read_x_and_y_values ( const std::string &path , std::vector < T > &xValues , std::vector < T > &yValues )
{
    std::fstream firstDataStream;
    firstDataStream.open ( path , std::ios::in );
    std::string line;
    std::size_t lineNo = 0;
    while ( firstDataStream >> line )
    {
        if ( lineNo == 0 )
        {
            lineNo++;
            continue;
        }
        lineNo++;
        std::stringstream ss ( line , std::ios::in );
        std::string colValue;
        std::size_t i = 0;
        while ( getline ( ss , colValue , ',' ) )
        {
            if ( i == 0 )
            {
                xValues.push_back ( parse_string_to_float_type < T > ( colValue ) );
            }
            else if ( i == 1 )
            {
                yValues.push_back ( parse_string_to_float_type < T > ( colValue ) );
            }
            i++;
        }
    }
}
template < class T >
void print_matrix ( Core::Matrix < T > &mat )
{
    size_t numOfRows = mat.numOfRows ();
    size_t numOfColumn = mat.numOfColumns ();
    for ( std::size_t i = 0; i < numOfRows; ++i )
    {
        for ( std::size_t j = 0; j < numOfColumn; ++j )
        {
            printf ( "%-5.2 " , mat ( i + 1 , j + 1 ) );
        }
        printf ( "\n" );
    }
    printf ( "\n" );
}
template < class T >
void print_prediction_result ( const std::vector < T > &xValues , const std::vector < T > &yValues , const std::vector < T > &predictedYValues , const std::string &outputFilePath )
{
    std::ofstream out ( outputFilePath , std::ios::trunc | std::ios::out );
    printf ( "X,Y,Y',Diff\n" );
    out << "X,Y,Y',Diff\n";
    for ( std::size_t i = 0; i < xValues.size (); ++i )
    {
        T x = xValues[ i ];
        T y = yValues[ i ];
        T yPred = predictedYValues[ i ];
        T diff = std::fabs ( y - yPred );
        std::string formatString = "X = ";
        formatString += get_padded_float_format < T > ();
        formatString += " , Y = ";
        formatString += get_padded_float_format < T > ();
        formatString += " , Y` = ";
        formatString += get_padded_float_format < T > ();
        formatString += " , Diff = ";
        formatString += get_padded_float_format < T > ();
        formatString += " \n";
        printf ( formatString.c_str () , x , y , yPred , diff );
        formatString = get_unpaded_float_format < T > ();
        formatString += ",";
        formatString += get_unpaded_float_format < T > ();
        formatString += ",";
        formatString += get_unpaded_float_format < T > ();
        formatString += ",";
        formatString += get_unpaded_float_format < T > ();
        formatString += "\n";
        out << string_format ( formatString , x , y , yPred , diff );
    }
    out.flush ();
    out.close ();
    printf ( "\n" );
}
template < class T >
void print_coefficients ( std::vector < T > coefficients , const std::string &filePath )
{
    std::ofstream out ( filePath , std::ios::trunc | std::ios::out );
    for ( std::size_t i = 0; i < coefficients.size (); ++i )
    {
        out << string_format ( get_unpaded_float_format < T > () + "\n" , coefficients[ i ] );
    }
    out.flush ();
    out.close ();
    printf ( "\n" );
}
template < class T >
T parse_string_to_float_type ( std::string &toParse )
{
    return std::stold ( toParse );
}
template <>
float parse_string_to_float_type ( std::string &toParse )
{
    return std::stof ( toParse );
}
template <>
double parse_string_to_float_type ( std::string &toParse )
{
    return std::stod ( toParse );
}
template <>
long double parse_string_to_float_type ( std::string &toParse )
{
    return std::stold ( toParse );
}
template < class T >
std::string get_padded_float_format ()
{
    return "%-25.20Lf";
}
template <>
std::string get_padded_float_format < float > ()
{
    return "%-25.20f";
}
template <>
std::string get_padded_float_format < double > ()
{
    return "%-25.20lf";
}
template <>
std::string get_padded_float_format < long double > ()
{
    return "%-25.20Lf";
}
template < class T >
std::string get_unpaded_float_format ()
{
    return "%.45Lf";
}
template <>
std::string get_unpaded_float_format < float > ()
{
    return "%.45f";
}
template <>
std::string get_unpaded_float_format < double > ()
{
    return "%.45lf";
}
template <>
std::string get_unpaded_float_format < long double > ()
{
    return "%.45Lf";
}
template < typename ... Args >
std::string string_format ( const std::string &format , Args ... args )
{
    int size = snprintf ( nullptr , 0 , format.c_str () , args ... ) + 1; // Extra space for '\0'
    if ( size <= 0 )
    {
        throw std::runtime_error ( "Error during formatting." );
    }
    std::unique_ptr < char[] > buf ( new char[size] );
    snprintf ( buf.get () , static_cast<std::size_t>(size) , format.c_str () , args ... );
    return std::string ( buf.get () , buf.get () + size - 1 ); // We don't want the '\0' inside
}

