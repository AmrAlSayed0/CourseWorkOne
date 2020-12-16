#ifndef COURSEWORKONE_CUBICSPLINEINTERPOLATION_HPP
#define COURSEWORKONE_CUBICSPLINEINTERPOLATION_HPP
#include <vector>
#include <stdexcept>
#include "../../MatrixLib/Matrix.hpp"
namespace Solution
{
    namespace Part3
    {
        template < class T > class CubicSplineInterpolation
        {
        private:
            bool isFit = false;
            std::vector < T > xValues;
            std::vector < T > yValues;
            std::vector < T > xCoeffs;
            T getSecondDerivative ( std::size_t index );
            T interpolateInner ( T x );
        public:
            CubicSplineInterpolation ();
            void fit ( const std::vector < T > &x , const std::vector < T > &y );
            std::vector < T > interpolate ( const std::vector < T > &x );
            std::vector < T > getCoefficients ();
        };
        template < class T >
        T CubicSplineInterpolation < T >::getSecondDerivative ( std::size_t index )
        {
            if ( index == 0 || index == this->xCoeffs.size () )
            {
                return 0;
            }
            return this->xCoeffs[ index - 1 ];
        }
        template < class T >
        T CubicSplineInterpolation < T >::interpolateInner ( T x )
        {
            if ( x < this->xValues[ 0 ] || x > this->xValues[ this->xValues.size () - 1 ] )
            {
                return std::numeric_limits < T >::min ();
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
            return ( ( d2f_im1 * std::pow ( xi - x , 3 ) ) / ( 6 * ximXim1 ) ) +
                   ( ( d2f_i * std::pow ( x - xim1 , 3 ) ) / ( 6 * ximXim1 ) ) +
                   ( ( ( yim1 / ximXim1 ) - ( ( d2f_im1 * ximXim1 ) / 6 ) ) * ( xi - x ) ) +
                   ( ( ( yi / ximXim1 ) - ( ( d2f_i * ximXim1 ) / 6 ) ) * ( x - xim1 ) );
            // @formatter:on
        }
        template < class T >
        CubicSplineInterpolation < T >::CubicSplineInterpolation ()
        {
            this->xValues = std::vector < T > ();
            this->yValues = std::vector < T > ();
            this->xCoeffs = std::vector < T > ();
        }
        template < class T >
        void CubicSplineInterpolation < T >::fit ( const std::vector < T > &x , const std::vector < T > &y )
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
                    aCoeffs[ i ] = xi - xim1;
                }
                if ( i != matSize - 1 )
                {
                    cCoeffs[ i ] = xip1 - xi;
                }
                bCoeffs[ i ] = 2 * ( xip1 - xim1 );
                dCoeffs[ i ] = ( -6 ) * ( ( ( yi - yim1 ) / ( xi - xim1 ) ) - ( ( yip1 - yi ) / ( xip1 - xi ) ) );
            }
            this->xCoeffs.resize ( matSize );
            T w;
            for ( std::size_t i = 1; i < matSize; ++i )
            {
                w = aCoeffs[ i ] / bCoeffs[ i - 1 ];
                bCoeffs[ i ] = bCoeffs[ i ] - w * cCoeffs[ i - 1 ];
                dCoeffs[ i ] = dCoeffs[ i ] - w * dCoeffs[ i - 1 ];
            }
            this->xCoeffs[ matSize - 1 ] = dCoeffs[ matSize - 1 ] / bCoeffs[ matSize - 1 ];
            for ( int i = ( ( int ) matSize ) - 2; i >= 0; i-- )
            {
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
        template < class T >
        std::vector < T > CubicSplineInterpolation < T >::interpolate ( const std::vector < T > &x )
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
        std::vector < T > CubicSplineInterpolation < T >::getCoefficients ()
        {
            return this->xCoeffs;
        }
    }
}
#endif //COURSEWORKONE_CUBICSPLINEINTERPOLATION_HPP
