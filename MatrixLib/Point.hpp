#ifndef COURSEWORKONE_POINT_HPP
#define COURSEWORKONE_POINT_HPP
#include <utility>
namespace Core
{
    template < class T >
    struct Point
    {
    public:
        T X;
        T Y;
        Point ( T x , T y );
        Point ( const Point < T > & other );
        Point ( Point < T > && other ) noexcept;
        ~Point ();
        Point < T > & operator = ( const Point < T > & rhs );
        Point < T > & operator = ( Point < T > && rhs ) noexcept;
    };
    template < class T >
    Point < T >::Point ( T x , T y )
        :X ( x ) ,
         Y ( y )
    {
    }
    template < class T >
    Point < T >::Point ( const Point < T > & other )
        :X ( other.X ) ,
         Y ( other.Y )
    {
    }
    template < class T >
    Point < T >::Point ( Point < T > && other ) noexcept
        :X ( std::exchange ( ( T & ) other.X , ( T && ) 0 ) ) ,
         Y ( std::exchange ( ( T & ) other.Y , ( T && ) 0 ) )
    {
    }
    template < class T >
    Point < T >::~Point ()
    {
    }
    template < class T >
    Point < T > & Point < T >::operator = ( const Point < T > & rhs )
    {
        if ( this == &rhs )
        {
            return *this;
        }
        Point < T > temp ( rhs );
        std::swap ( ( T & ) this->X , ( T & ) temp.X );
        std::swap ( ( T & ) this->Y , ( T & ) temp.Y );
        return *this;
    }
    template < class T >
    Point < T > & Point < T >::operator = ( Point < T > && rhs ) noexcept
    {
        this->X = std::exchange ( rhs.X , 0 );
        this->Y = std::exchange ( rhs.Y , 0 );
        return *this;
    }
}
#endif //COURSEWORKONE_POINT_HPP
