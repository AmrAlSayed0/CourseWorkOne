/*
 * Interpolator.hpp
 *
 *  Created on: Dec 13, 2020
 *      Author: Amr Al-Sayed
 */
#ifndef COURSEWORKONE_INTERPOLATOR_HPP
#define COURSEWORKONE_INTERPOLATOR_HPP
#include <vector>
namespace Solution::Part3
{
    /**
     * @brief A class used to do Newton's Polynomial Interpolation over a series of points.
     */
    template < class T >
    class Interpolator
    {
    public:
        /**
         * @brief Used to build a polynomial that fit the supplied points. This should be the first method to use on this class.
         * @param x The X values of the points to fit.
         * @param y The Y values of the pints to fit.
         */
        virtual void fit ( const std::vector < T > & x , const std::vector < T > & y ) = 0;
        /**
         * @brief Calculates interpolated values for the supplied X values. The method "fit" MUST be called before calling this method.
         * @param x The X values to calculate y values for.
         * @return
         */
        virtual std::vector < T > interpolate ( const std::vector < T > & x ) = 0;
        /**
         * @brief Get the values of the bᵢ coefficients after the fit.
         * @return The values of the bᵢ coefficients. Returns an empty vector if "fit" was never called.
         */
        virtual std::vector < T > getCoefficients () = 0;
    };
}
#endif //COURSEWORKONE_INTERPOLATOR_HPP
