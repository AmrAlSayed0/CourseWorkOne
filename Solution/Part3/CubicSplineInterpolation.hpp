#ifndef COURSEWORKONE_CUBICSPLINEINTERPOLATION_HPP
#define COURSEWORKONE_CUBICSPLINEINTERPOLATION_HPP
#include <vector>
namespace Solution
{
    namespace Part3
    {
        template < class T > class CubicSplineInterpolation
        {
        private:
            bool isFit = false;
            T interpolateInner ( T x );
        public:
            CubicSplineInterpolation ();
            void fit ( const std::vector < T > &x , const std::vector < T > &y );
            std::vector < T > interpolate ( const std::vector < T > &x );
            std::vector < T > getCoefficients ();
        };
        template < class T >
        T CubicSplineInterpolation < T >::interpolateInner ( T x )
        {
            return static_cast < T > ( 0 );
        }
        template < class T >
        CubicSplineInterpolation < T >::CubicSplineInterpolation ()
        {
        }
        template < class T >
        void CubicSplineInterpolation < T >::fit ( const std::vector < T > &x , const std::vector < T > &y )
        {
        }
        template < class T >
        std::vector < T > CubicSplineInterpolation < T >::interpolate ( const std::vector < T > &x )
        {
            return std::vector < T > ();
        }
        template < class T >
        std::vector < T > CubicSplineInterpolation < T >::getCoefficients ()
        {
            return std::vector < T > ();
        }
    }
}
#endif //COURSEWORKONE_CUBICSPLINEINTERPOLATION_HPP
