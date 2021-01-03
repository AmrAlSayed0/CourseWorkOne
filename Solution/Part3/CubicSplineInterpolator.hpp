/*
 * CubicSplineInterpolator.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Amr Al-Sayed
 */
#ifndef COURSEWORKONE_CUBICSPLINEINTERPOLATOR_HPP
#define COURSEWORKONE_CUBICSPLINEINTERPOLATOR_HPP
#include <vector>
#include <stdexcept>
#include <limits>
#include <cmath>
#include "Interpolator.hpp"
namespace Solution::Part3
{
    template < class T >
    class CubicSplineInterpolator
        : public Interpolator < T >
    {
    private:
        bool isFit = false;
        std::vector < T > xValues;
        std::vector < T > yValues;
        std::vector < T > xCoeffs;
        T getSecondDerivative ( std::size_t index )
        {
            if ( index == 0 || index == this->xValues.size () - 1 )
            {
                return 0;
            }
            return this->xCoeffs[ index - 1 ];
        }
        T interpolateInner ( T x )
        {
            if ( x < this->xValues[ 0 ] || x > this->xValues[ this->xValues.size () - 1 ] )
            {
                return std::numeric_limits < T >::min ();
            }
            if ( x == this->xValues[ 0 ] )
            {
                return this->yValues[ 0 ];
            }
            if ( x == this->xValues[ this->xValues.size () - 1 ] )
            {
                return this->yValues[ this->xValues.size () - 1 ];
            }
            std::size_t i = 1;
            while ( true )
            {
                if ( x >= this->xValues[ i - 1 ] && x <= this->xValues[ i ] )
                {
                    break;
                }
                i++;
            }
            const T xi = this->xValues[ i ];
            const T xim1 = this->xValues[ i - 1 ];
            const T yi = this->yValues[ i ];
            const T yim1 = this->yValues[ i - 1 ];
            const T d2f_i = getSecondDerivative ( i );
            const T d2f_im1 = getSecondDerivative ( i - 1 );
            const T ximXim1 = xi - xim1;
            // @formatter:off
            const T firstTerm = ( ( d2f_im1 * std::pow ( xi - x , 3 ) ) / ( 6 * ximXim1 ) );
            const T secondTerm = ( ( d2f_i * std::pow ( x - xim1 , 3 ) ) / ( 6 * ximXim1 ) );
            const T thirdTerm = ( ( ( yim1 / ximXim1 ) - ( ( d2f_im1 * ximXim1 ) / 6 ) ) * ( xi - x ) );
            const T fourthTerm = ( ( ( yi / ximXim1 ) - ( ( d2f_i * ximXim1 ) / 6 ) ) * ( x - xim1 ) );
            return firstTerm +
                   secondTerm +
                   thirdTerm +
                   fourthTerm;
            //            return ( ( d2f_im1 * std::pow ( xi - x , 3 ) ) / ( 6 * ximXim1 ) ) +
            //                   ( ( d2f_i * std::pow ( x - xim1 , 3 ) ) / ( 6 * ximXim1 ) ) +
            //                   ( ( ( yim1 / ximXim1 ) - ( ( d2f_im1 * ximXim1 ) / 6 ) ) * ( xi - x ) ) +
            //                   ( ( ( yi / ximXim1 ) - ( ( d2f_i * ximXim1 ) / 6 ) ) * ( x - xim1 ) );
            // @formatter:on
        }
    public:
        CubicSplineInterpolator ()
        {
            this->xValues = std::vector < T > ();
            this->yValues = std::vector < T > ();
            this->xCoeffs = std::vector < T > ();
        }
        void fit ( const std::vector < T > & x , const std::vector < T > & y ) override
        {
            if ( x.size () != y.size () )
            {
                throw std::invalid_argument ( "The 2 vectors must be of the same size." );
            }
            std::size_t n = x.size ();
            const size_t matSize = n - 2;
            std::vector < T > aCoeffs = std::vector < T > ( matSize );
            std::vector < T > bCoeffs = std::vector < T > ( matSize );
            std::vector < T > cCoeffs = std::vector < T > ( matSize );
            std::vector < T > dCoeffs = std::vector < T > ( matSize );
            for ( std::size_t i = 0; i < matSize; ++i )
            {
                const T xim1 = x[ i ];
                const T xi = x[ i + 1 ];
                const T xip1 = x[ i + 2 ];
                const T yim1 = y[ i ];
                const T yi = y[ i + 1 ];
                const T yip1 = y[ i + 2 ];
                if ( i != 0 )
                {
                    /** ( 𝑥ᵢ - 𝑥ᵢ₋₁ )𝑓″( 𝑥ᵢ₋₁ ) */
                    aCoeffs[ i ] = xi - xim1;
                }
                if ( i != matSize - 1 )
                {
                    /** ( 𝑥ᵢ₊₁ - 𝑥ᵢ )𝑓″( 𝑥ᵢ₊₁ ) */
                    cCoeffs[ i ] = xip1 - xi;
                }
                /** 2 ( 𝑥ᵢ₊₁ - 𝑥ᵢ₋₁ ) */
                bCoeffs[ i ] = 2 * ( xip1 - xim1 );
                /** -6 ( ( ( 𝑦ᵢ - 𝑦ᵢ₋₁ ) / ( 𝑥ᵢ - 𝑥ᵢ₋₁ ) ) - ( ( 𝑦ᵢ₊₁ - 𝑦ᵢ ) / ( 𝑥ᵢ₊₁ - 𝑥ᵢ ) ) ) */
                dCoeffs[ i ] = ( -6 ) * ( ( ( yi - yim1 ) / ( xi - xim1 ) ) - ( ( yip1 - yi ) / ( xip1 - xi ) ) );
            }
            this->xCoeffs.resize ( matSize );
            /** Thomas' algorithm */
            T w;
            for ( std::size_t i = 1; i < matSize; ++i )
            {
                /** w = 𝑎ᵢ / 𝑏ᵢ₋₁ */
                w = aCoeffs[ i ] / bCoeffs[ i - 1 ];
                /** 𝑏ᵢ ≔ 𝑏ᵢ - 𝑤𝑐ᵢ₋₁ */
                bCoeffs[ i ] = bCoeffs[ i ] - w * cCoeffs[ i - 1 ];
                /** 𝑑ᵢ ≔ 𝑑ᵢ - 𝑤𝑑ᵢ₋₁ */
                dCoeffs[ i ] = dCoeffs[ i ] - w * dCoeffs[ i - 1 ];
            }
            /** Back Substitution */
            /** 𝑥ₙ = 𝑑ₙ / 𝑏ₙ */
            this->xCoeffs[ matSize - 1 ] = dCoeffs[ matSize - 1 ] / bCoeffs[ matSize - 1 ];
            for ( int i = ( ( int ) matSize ) - 2; i >= 0; i-- )
            {
                /** 𝑥ᵢ = 𝑑ᵢ − 𝑐ᵢ𝑥ᵢ₊₁ / 𝑏ᵢ */
                this->xCoeffs[ i ] = ( dCoeffs[ i ] - cCoeffs[ i ] * this->xCoeffs[ i + 1 ] ) / bCoeffs[ i ];
            }
            this->xValues.clear ();
            this->xValues.resize ( n );
            for ( int i = 0; i < n; ++i )
            {
                this->xValues[ i ] = x[ i ];
            }
            this->yValues.clear ();
            this->yValues.resize ( n );
            for ( int i = 0; i < n; ++i )
            {
                this->yValues[ i ] = y[ i ];
            }
            this->isFit = true;
        }
        std::vector < T > interpolate ( const std::vector < T > & x ) override
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
        std::vector < T > getCoefficients () override
        {
            std::vector < T > result ( this->xCoeffs );
            result.insert ( result.begin () , ( T && ) 0 );
            result.push_back ( ( T ) 0 );
            return result;
        }
    };
}
#endif //COURSEWORKONE_CUBICSPLINEINTERPOLATOR_HPP
