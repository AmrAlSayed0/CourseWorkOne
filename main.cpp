#include <cstdio>
#include "MatrixLib/Matrix.hpp"
template < class T >
void print_matrix ( Core::Matrix < T > &mat );
int main ()
{
    Core::Matrix < long double > a ( 1 , 5 , ( long double ) 0 );
    a ( 1 , 1 ) = 1;
    a ( 1 , 2 ) = 2;
    a ( 1 , 3 ) = 3;
    a ( 1 , 4 ) = 4;
    a ( 1 , 5 ) = 5;
    print_matrix ( a );
    a.transpose ();
    print_matrix ( a );
    Core::Matrix < Core::Matrix < long double >::element_type > b = Core::Matrix < long double >::identity ( 5 );
    print_matrix ( b );
    Core::Matrix < long double > c = a * ( long double ) 5;
    print_matrix ( c );
    auto func = [] ( long double elem ) -> long double
    {
        return elem * 500;
    };
    c.each ( func );
    print_matrix ( c );
    c = Core::Matrix < long double >::augment ( a , b );
    print_matrix ( c );
    return 0;
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
            printf ( "%-5.2Lf " , mat ( i + 1 , j + 1 ) );
        }
        printf ( "\n" );
    }
    printf ( "\n" );
}
