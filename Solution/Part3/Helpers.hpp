/*
 * Helpers.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Amr Al-Sayed
 */
#ifndef COURSEWORKONE_HELPERS_HPP
#define COURSEWORKONE_HELPERS_HPP
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
namespace Helpers
{
    template < class T >
    T strToFloat ( std::string & toParse )
    {
        return std::stold ( toParse );
    }
    template <>
    float strToFloat < float > ( std::string & toParse )
    {
        return std::stof ( toParse );
    }
    template <>
    double strToFloat < double > ( std::string & toParse )
    {
        return std::stod ( toParse );
    }
    template <>
    long double strToFloat < long double > ( std::string & toParse )
    {
        return std::stold ( toParse );
    }
    template < class T >
    std::string getFloatFormat ()
    {
        return "Lf";
    }
    template <>
    std::string getFloatFormat < float > ()
    {
        return "f";
    }
    template <>
    std::string getFloatFormat < double > ()
    {
        return "lf";
    }
    template <>
    std::string getFloatFormat < long double > ()
    {
        return "Lf";
    }
    template < typename ... Args >
    std::string string_format ( const std::string & format , Args ... args )
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
}
//**********************************************************************//
//                                                                      //
//                             DECLARATIONS                             //
//                                                                      //
//**********************************************************************//

template < class T >
void readXAndYValues ( const std::string & path , std::vector < T > & xValues , std::vector < T > & yValues );
template < class T >
std::vector < T > getTestXs ( std::vector < T > & vector );
template < class T >
void printPredictionResult ( const std::vector < T > & xValues , const std::vector < T > & yValues , const std::vector < T > & predictedYValues , const std::string & outputFilePath );
template < class T >
void printCoefficients ( std::vector < T > coefficients , const std::string & filePath );
//**********************************************************************//
//                                                                      //
//                           IMPLEMENTATIONS                            //
//                                                                      //
//**********************************************************************//

template < class T >
void readXAndYValues ( const std::string & path , std::vector < T > & xValues , std::vector < T > & yValues )
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
                xValues.push_back ( Helpers::strToFloat < T > ( colValue ) );
            }
            else if ( i == 1 )
            {
                yValues.push_back ( Helpers::strToFloat < T > ( colValue ) );
            }
            i++;
        }
    }
}
template < class T >
std::vector < T > getTestXs ( std::vector < T > & vector )
{
    T maxX = *( std::max_element ( vector.begin () , vector.end () ) );
    T minX = *( std::min_element ( vector.begin () , vector.end () ) );
    T diff = maxX - minX;
    constexpr size_t size = 500;
    std::vector < T > result ( size );
    result[ 0 ] = maxX;
    result[ size - 1 ] = minX;
    T diffInterval = diff / ( ( T ) ( size - 1 ) );
    for ( std::size_t i = 1; i < size - 1; ++i )
    {
        result[ i ] = result[ i - 1 ] - diffInterval;
    }
    return result;
}
template < class T >
void printPredictionResult ( const std::vector < T > & xValues , const std::vector < T > & yValues , const std::vector < T > & predictedYValues , const std::string & outputFilePath )
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
        std::string formatString;
        /*
                formatString = "X = %-50.45";
                formatString += Helpers::getFloatFormat < T > ();
                formatString += " , Y = %-50.45";
                formatString += Helpers::getFloatFormat < T > ();
                formatString += " , Y` = %-50.45";
                formatString += Helpers::getFloatFormat < T > ();
                formatString += " , Diff = %-50.45";
                formatString += Helpers::getFloatFormat < T > ();
                formatString += " \n";
                printf ( formatString.c_str () , x , y , yPred , diff );
        */
        formatString = "%-47.45";
        formatString += Helpers::getFloatFormat < T > ();
        formatString += ",%-47.45";
        formatString += Helpers::getFloatFormat < T > ();
        formatString += ",%-47.45";
        formatString += Helpers::getFloatFormat < T > ();
        formatString += ",%-47.45";
        formatString += Helpers::getFloatFormat < T > ();
        formatString += "\n";
        out << Helpers::string_format ( formatString , x , y , yPred , diff );
    }
    out.flush ();
    out.close ();
    printf ( "\n" );
}
template < class T >
void printCoefficients ( std::vector < T > coefficients , const std::string & filePath )
{
    std::ofstream out ( filePath , std::ios::trunc | std::ios::out );
    for ( std::size_t i = 0; i < coefficients.size (); ++i )
    {
        out << Helpers::string_format ( "%.45" + Helpers::getFloatFormat < T > () + "\n" , coefficients[ i ] );
    }
    out.flush ();
    out.close ();
    printf ( "\n" );
}
#endif //COURSEWORKONE_HELPERS_HPP
