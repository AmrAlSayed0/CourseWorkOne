#ifndef COURSEWORKONE_NEWTONINTERPOLATION_HPP
#define COURSEWORKONE_NEWTONINTERPOLATION_HPP
#include <vector>
#include <stdexcept>
#include "../../MatrixLib/Matrix.hpp"
namespace Solution
{
    namespace Part3
    {
        /**
         * @brief A class used to do Newton's Polynomial Interpolation over a series of points.
         */
        template < class T > class NewtonInterpolation
        {
        private:
            /**
             * @brief Indicates if the class is ready to interpolate new points.
             */
            bool isFit = false;
            /**
             * @brief The original X values of the points used to make the fit. (Needed for interpolating new points).
             */
            std::vector < T > xValues;
            /**
             * @brief The values of the calculated bᵢ coefficients after the fit.
             */
            std::vector < T > bValues;
            /**
             * @brief Inner function used to calculate the interpolated value of one point.
             * @param x The X value to interpolate.
             * @return The interpolated Y value.
             */
            T interpolateInner ( T x );
        public:
            /**
             * @brief Default constructor. Does nothing.
             */
            NewtonInterpolation ();
            /**
             * @brief Used to build a polynomial that fit the supplied points. This should be the first method to use on this class.
             * @param x The X values of the points to fit.
             * @param y The Y values of the pints to fit.
             */
            void fit ( const std::vector < T > &x , const std::vector < T > &y );
            /**
             * @brief Calculates interpolated values for the supplied X values. The method "fit" MUST be called before calling this method.
             * @param x The X values to calculate y values for.
             * @return
             */
            std::vector < T > interpolate ( const std::vector < T > &x );
            /**
             * @brief Get the values of the bᵢ coefficients after the fit.
             * @return The values of the bᵢ coefficients. Returns an empty vector if "fit" was never called.
             */
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
            std::size_t n = this->bValues.size ();
            if ( x < this->xValues[ 0 ] || x > this->xValues[ n - 1 ] )
            {
                return std::numeric_limits < T >::min ();
            }
            T result = 0;
            /** 𝑓ₙ(𝑥) = b₀ + b₁(𝑥−𝑥₀) + ⋯ + bₙ(𝑥−𝑥₀)(𝑥−𝑥₁)⋯(𝑥−𝑥ₙ₋₁) */
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
            /** If the x values are more than the y values, there will be x values that have no corresponding y value. The fit can't be completed */
            if ( x.size () > y.size () )
            {
                throw std::invalid_argument ( "The 2 vectors must be of the same size." );
            }
            std::size_t n = x.size ();
            /** This is a store for the intermediate calculations. Will be discarded in the end */
            std::vector < T > calculationVector = std::vector < T > ( n );
            /** Clear and resize the bᵢ values to allow the same class to be used with multiple fits */
            this->bValues.clear ();
            this->bValues.resize ( n );
            for ( std::size_t i = 0; i < n; ++i )
            {
                if ( i == 0 )
                {
                    /** Initialize the vector with the y values that will be used in the following iterations */
                    for ( std::size_t j = 0; j < n; ++j )
                    {
                        calculationVector[ j ] = y[ j ];
                    }
                }
                else
                {
                    /** 𝑓[𝑥ₙ,𝑥ₙ₋₁,...,𝑥₁,𝑥₀] = ( 𝑓[𝑥ₙ,𝑥ₙ₋₁,...,𝑥₁] - 𝑓[𝑥ₙ₋₁,𝑥ₙ₋₂,...,𝑥₀] ) / ( 𝑥ₙ − 𝑥₀ ) */
                    for ( std::size_t j = 0; j < ( n - i ); ++j )
                    {
                        calculationVector[ j ] = ( ( calculationVector[ j + 1 ] - calculationVector[ j ] ) / ( x[ j + i ] - x[ j ] ) );
                    }
                }
                this->bValues[ i ] = calculationVector[ 0 ];
            }
            /** Saving the X values too because it is needed for the interpolation */
            this->xValues.clear ();
            this->xValues.resize ( n );
            for ( int i = 0; i < n; ++i )
            {
                this->xValues[ i ] = x[ i ];
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
