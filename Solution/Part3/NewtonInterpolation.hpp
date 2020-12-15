#ifndef COURSEWORKONE_NEWTONINTERPOLATION_HPP
#define COURSEWORKONE_NEWTONINTERPOLATION_HPP
#include <vector>
#include <stdexcept>
#include "../../MatrixLib/Matrix.hpp"
namespace Solution
{
    namespace Part3
    {
        template < class T > class NewtonInterpolation
        {
        private:
            bool isFit = false;
            std::vector < T > xValues;
            std::vector < T > bValues;
            T interpolateInner ( T x );
        public:
            NewtonInterpolation ();
            void fit ( const std::vector < T > &x , const std::vector < T > &y );
            std::vector < T > interpolate ( const std::vector < T > &x );
            std::vector < T > getCoefficients ();
        };
        template < class T >
        NewtonInterpolation < T >::NewtonInterpolation ()
        {
            this->xValues = std::vector < T > ();
            this->bValues = std::vector < T > ();
        }
        template < class T >
        T NewtonInterpolation < T >::interpolateInner ( T x )
        {
            T result = 0;
            std::size_t n = this->bValues.size ();
            for ( std::size_t i = 0; i < n; ++i )
            {
                T product = this->bValues[ i ];
                for ( std::size_t j = 0; j < i; ++j )
                {
                    product *= ( x - this->xValues[ j ] );
                }
                result += product;
            }
            return result;
        }
        template < class T >
        void NewtonInterpolation < T >::fit ( const std::vector < T > &x , const std::vector < T > &y )
        {
            if ( x.size () != y.size () )
            {
                throw std::invalid_argument ( "The 2 vectors must be of the same size." );
            }
            std::size_t n = x.size ();
            std::vector < T > calculationVector = std::vector < T > ( n );
            this->bValues.clear ();
            for ( std::size_t i = 0; i < n; ++i )
            {
                if ( i == 0 )
                {
                    for ( std::size_t j = 0; j < n; ++j )
                    {
                        calculationVector[ j ] = y[ j ];
                    }
                }
                else
                {
                    for ( std::size_t j = 0; j < ( n - i ); ++j )
                    {
                        calculationVector[ j ] = ( ( calculationVector[ j + 1 ] - calculationVector[ j ] ) / ( x[ j + i ] - x[ j ] ) );
                    }
                }
                this->bValues.push_back ( calculationVector[ 0 ] );
            }
            this->xValues.clear ();
            for ( int i = 0; i < n; ++i )
            {
                this->xValues.push_back ( x[ i ] );
            }
            this->isFit = true;
        }
        template < class T >
        std::vector < T > NewtonInterpolation < T >::interpolate ( const std::vector < T > &x )
        {
            if ( !this->isFit )
            {
                return std::vector < T > ();
            }
            std::size_t n = x.size ();
            std::vector < T > resultVector = std::vector < T > ( n );
            for ( std::size_t i = 0; i < n; ++i )
            {
                resultVector[ i ] = this->interpolateInner ( x[ i ] );
            }
            return resultVector;
        }
        template < class T >
        std::vector < T > NewtonInterpolation < T >::getCoefficients ()
        {
            return this->bValues;
        }
    }
}
#endif //COURSEWORKONE_NEWTONINTERPOLATION_HPP
