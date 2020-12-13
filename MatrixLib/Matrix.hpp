#ifndef MATRIXLIB_MATRIX_H
#define MATRIXLIB_MATRIX_H
#include <climits>
#include <cstddef>
#include <cmath>
#include <type_traits>
#include <stdexcept>
#include <utility>
#include <cstring>
#include <vector>
#include <functional>
#include <limits>
namespace Core
{
    /**
     * @brief Represents a matrix of arbitrary size.
     * @tparam T A floating point type to be used for calculations.
     */
    template < class T > class Matrix
    {
    private:
        /**
         * @brief Swaps the contents of one matrix with the contents of another.
         * @param first The first matrix to swap.
         * @param second The second matrix to swap
         */
        static void swap ( Matrix < T > &first , Matrix < T > &second );
        /**
         * @brief Number of rows in the matrix. If this is 0, the number of columns must be 0.
         */
        std::size_t _numOfRows = 0;
        /**
         * @brief Number of columns in the matrix. If this is 0, the number of rows must be 0.
         */
        std::size_t _numOfColumns = 0;
        /**
         * @brief The values in the matrix as a contiguous array of values. The array format is [ sizeof ( T ) * _numOfRows ] * _numOfColumns. To access the value at row i and column j _data [ ( i - 1 ) * _numOfColumns + ( j - 1 ) ] where i >= 1 and j >= 1
         */
        T * _data = nullptr;
        /**
         * @brief Sets the other dimension to 0 if one of the dimensions is 0.
         */
        void fixSizeIfZero ();
        /**
         * @brief Checks if the given numbers are within the bounds of the matrix and throws an std::out_of_bounds exception if it is not
         * @param i The row number to check
         * @param j The column number to check
         */
        void checkBounds ( std::size_t i , std::size_t j ) const;
        T getElementInner ( std::size_t i , std::size_t j ) const;
    public:
        using element_type = T;
        /**
         * @brief Creates an identity matrix with the specified size.
         * @param numOfRowsOrColumns The size of the matrix, both width and height.
         * @return
         */
        static Matrix < T > identity ( std::size_t numOfRowsOrColumns );
        /**
         * @brief Augments the second matrix on to the first one and returns a new matrix. Both matricies must have the same number of rows.
         * @param A The matrix to augment to.
         * @param B The matrix to augment with.
         * @return A new matrix that is the result of the augmentation.
         */
        static Matrix < T > augment ( const Matrix < T > &A , const Matrix < T > &B );
        /**
         * @brief Constructs a 0 x 0 matrix.
         */
        Matrix ();
        /**
         * @brief Constructs a matrix of the desired size and zeros it out.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         */
        Matrix ( std::size_t numOfRows , std::size_t numOfColumns );
        /**
         * @brief Constructs a matrix of the desired size and fills all the cells with the provided value.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         * @param value The value that the matrix should be filled with.
         */
        Matrix ( std::size_t numOfRows , std::size_t numOfColumns , T value );
        /**
         * @brief Constructs a matrix of the desired size and fills all the cells with the provided data.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         * @param data The data that the matrix should be filled with. This must be in the form of a contiguous array of values. Must be at least numOfRows * numOfColumns long.
         */
        Matrix ( std::size_t numOfRows , std::size_t numOfColumns , T const * data );
        /**
         * @brief Constructs a matrix of the desired size and fills all the cells with the provided data.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         * @param data he data that the matrix should be filled with. This must be in the form of an array of arrays. The outer array must be of length numOfRows and each of the inner arrays must be numOfColumns long.
         */
        Matrix ( std::size_t numOfRows , std::size_t numOfColumns , T const * const * data );
        /**
         * @brief Copies the provided matrix into this one.
         * @param other The matrix to copy.
         */
        Matrix ( const Matrix < T > &other );
        /**
         * @brief Moves the provided matrix into this one. The other matrix is no longer usable.
         * @param other The matrix to move.
         */
        Matrix ( Matrix < T > &&other ) noexcept;
        /**
         * @brief Copies the right matrix into the left one.
         * @param rhs The rhs matrix that should be copied into this one.
         * @return A reference to the new copied into matrix
         */
        Matrix < T > &operator = ( const Matrix < T > &rhs );
        /**
         * @brief Moves the right matrix into the left one. The right matrix is no longer usable after the assignment.
         * @param rhs The other matrix that should be moved into this one.
         * @return A reference to the new moved into matrix
         */
        Matrix < T > &operator = ( Matrix < T > &&rhs ) noexcept;
        /**
         * @brief Cleans the matrix and deallocates the storage.
         */
        ~Matrix ();
        /**
         * @brief Gets the number of rows in the matrix.
         * @return The number of rows in the matrix.
         */
        std::size_t numOfRows () const;
        /**
         * @brief Gets the number of columns in the matrix.
         * @return The number of columns in the matrix.
         */
        std::size_t numOfColumns () const;
        /**
         * @brief Get the total number of elements in the matrix.
         * @return The total number of elements in the matrix
         */
        std::size_t numOfElements () const;
        /**
         * @brief Fills the entire matrix with the given value.
         * @param value The value to fill the matrix with
         */
        void fill ( T value );
        /**
         * @brief Gets the element at the specified row and column. This method doesn't do any bounds checking.
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return The element at row i and column j.
         */
        T &at ( std::size_t i , std::size_t j );
        /**
         * @brief Gets the element at the specified row and column. This method doesn't do any bounds checking. It returns an lvalue reference so it can be assigned directly.
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return A reference to the element at row i and column j.
         */
        T &operator () ( std::size_t i , std::size_t j );
        /**
         * @brief Gets the element at the specified row and column. This method does bound checking and throws std::out_of_range exception if i or j is out of bounds.
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return The element at row i and column j.
         */
        T getElement ( std::size_t i , std::size_t j ) const;
        /**
         * @brief Gets the row of the specified number as a vector. This vector points directly to the data and the data inside it would be invalid after an operation that changes the dimensions of the matrix
         * @param i The row number to get.
         * @return The specified row as a vector.
         */
        std::vector < T > operator [] ( std::size_t i );
        /**
         * @brief Checks if the matrix is a square matrix i.e m = n.
         * @return Whether the matrix is square or not.
         */
        bool isSquare () const;
        bool isVector () const;
        bool isColumn () const;
        bool isUpperTri () const;
        bool isLowerTri () const;
        bool isDiagonal () const;
        bool isSymmetric () const;
        /**
         * @brief Gets a copy of the specified row.
         * @param i The row number to get.
         * @return A copy of the specified row.
         */
        std::vector < T > row ( std::size_t i ) const;
        /**
         * @brief Gets a copy of the specified column.
         * @param j The column number to get.
         * @return A copy of the specified column.
         */
        std::vector < T > column ( std::size_t j ) const;
        /**
         * @brief Gets a copy of the diagonal of the matrix. This throws std::invalid_argument exception if the matrix is not square.
         * @return A copy of the diagonal
         */
        std::vector < T > diag () const;
        /**
         * @brief Adds the right matrix to this one. Must be of the same size.
         * @param right The matrix to add.
         * @return The modified matrix.
         */
        Matrix < T > &operator += ( const Matrix < T > &right );
        /**
         * @brief Subtracts the right matrix from this one. Must be of the same size.
         * @param right The matrix to subtract.
         * @return The modified matrix.
         */
        Matrix < T > &operator -= ( const Matrix < T > &right );
        /**
         * @brief Multiplies the right matrix with this one. This is a dot multiplication operation not an element-wise operation. The number of columns of the left matrix must be equal to the number of rows of the right matrix.
         * @param right The matrix to multiply by.
         * @return The modified matrix.
         */
        Matrix < T > &operator *= ( const Matrix < T > &right );
        /**
         * @brief Multiplies each element of the matrix with the given value.
         * @param right The value to multiply each element with.
         * @return The multiplied matrix.
         */
        Matrix < T > &operator *= ( const T &right );
        /**
         * @brief Divides each element of the matrix with the given value.
         * @param right The value to divide by.
         * @return The divided value.
         */
        Matrix < T > &operator /= ( const T &right );
        /**
         * @brief Transposes the matrix in-place.
         */
        void transpose ();
        /**
         * @brief Swaps the locations of the 2 rows in the matrix
         * @param i1 The row number of the first row to swap.
         * @param i2 The row number of the second row to swap.
         */
        void swapRows ( std::size_t i1 , std::size_t i2 );
        /**
         * @brief Transforms each element in the matrix using the provided function.
         * @param func The function to apply to each element.
         */
        void each ( std::function < T ( T ) > func );
    };
}
namespace Core
{
    template < class T >
    void Matrix < T >::swap ( Matrix < T > &first , Matrix < T > &second )
    {
        std::swap ( ( std::size_t & ) first._numOfRows , ( std::size_t & ) second._numOfRows );
        std::swap ( ( std::size_t & ) first._numOfColumns , ( std::size_t & ) second._numOfColumns );
        std::swap ( ( T *& ) first._data , ( T *& ) second._data );
    }
    template < class T >
    void Matrix < T >::fixSizeIfZero ()
    {
        if ( this->_numOfRows == 0 || this->_numOfColumns == 0 )
        {
            this->_numOfRows = 0;
            this->_numOfColumns = 0;
        }
    }
    template < class T >
    void Matrix < T >::checkBounds ( std::size_t i , std::size_t j ) const
    {
        if ( i - 1 > this->_numOfRows )
        {
            throw std::out_of_range ( "Row number can't be less than 1 or greater than " + ( this->_numOfRows + 1 ) );
        }
        if ( j - 1 > this->_numOfColumns )
        {
            throw std::out_of_range ( "Column number can't be less than 1 or greater than " + ( this->_numOfColumns + 1 ) );
        }
    }
    template < class T >
    T Matrix < T >::getElementInner ( std::size_t i , std::size_t j ) const
    {
        return this->_data[ ( ( i - 1 ) * this->_numOfColumns ) + ( j - 1 ) ];
    }
    template < class T >
    Matrix < T > Matrix < T >::identity ( std::size_t numOfRowsOrColumns )
    {
        Matrix < T > identityResult ( numOfRowsOrColumns , numOfRowsOrColumns );
        for ( std::size_t i = 1; i <= identityResult._numOfRows; ++i )
        {
            for ( std::size_t j = 1; j <= identityResult._numOfColumns; ++j )
            {
                if ( i != j )
                {
                    continue;
                }
                identityResult ( i , j ) = 1;
            }
        }
        return identityResult;
    }
    template < class T >
    Matrix < T > Matrix < T >::augment ( const Matrix < T > &A , const Matrix < T > &B )
    {
        if ( A._numOfRows != B._numOfRows )
        {
            throw std::invalid_argument ( "The augmented matrix must have the same number of rows as the matrix to augment with." );
        }
        Matrix AB ( A._numOfRows , A._numOfColumns + B._numOfColumns );
        for ( std::size_t i = 1; i <= AB._numOfRows; ++i )
        {
            for ( std::size_t j = 1; j <= AB._numOfColumns; ++j )
            {
                if ( j <= A._numOfColumns )
                {
                    AB ( i , j ) = A.getElementInner ( i , j );
                }
                else
                {
                    AB ( i , j ) = B.getElementInner ( i , j - A._numOfColumns );
                }
            }
        }
        return AB;
    }
    template < class T >
    Matrix < T >::Matrix ()
            : Matrix ( 0 , 0 )
    {
    }
    template < class T >
    Matrix < T >::Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns )
            : Matrix ( numOfRows , numOfColumns , ( T const ) 0 )
    {
    }
    template < class T >
    Matrix < T >::Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns , T const value )
            : _numOfRows ( numOfRows ) ,
              _numOfColumns ( numOfColumns )
    {
        this->fixSizeIfZero ();
        this->_data = new T[numOfRows * numOfColumns] {};
        this->fill ( value );
    }
    template < class T >
    Matrix < T >::Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns , T const * const data )
            : _numOfRows ( numOfRows ) ,
              _numOfColumns ( numOfColumns )
    {
        this->fixSizeIfZero ();
        _data = new T[numOfRows * numOfColumns] {};
        for ( std::size_t i = 0; i < this->_numOfRows; i++ )
        {
            for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
            {
                this->_data[ ( i * this->_numOfColumns ) + j ] = data[ ( i * this->_numOfColumns ) + j ];
            }
        }
    }
    template < class T >
    Matrix < T >::Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns , T const * const * const data )
            : _numOfRows ( numOfRows ) ,
              _numOfColumns ( numOfColumns )
    {
        this->fixSizeIfZero ();
        for ( std::size_t i = 0; i < this->_numOfRows; i++ )
        {
            for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
            {
                this->_data[ i * this->_numOfColumns + j ] = data[ i ][ j ];
            }
        }
    }
    template < class T >
    Matrix < T >::Matrix ( const Matrix < T > &other )
            : _numOfRows ( other._numOfRows ) ,
              _numOfColumns ( other._numOfColumns ) ,
              _data ( new T[other._numOfRows * other._numOfColumns] ) //Copy Constructor
    {
        std::memcpy ( ( void * ) this->_data , ( const void * ) other._data , this->_numOfRows * this->_numOfColumns * sizeof ( T ) );
    }
    template < class T >
    Matrix < T >::Matrix ( Matrix < T > &&other ) noexcept
            : _numOfRows ( std::exchange ( ( std::size_t & ) other._numOfRows , ( std::size_t && ) 0 ) ) ,
              _numOfColumns ( std::exchange ( ( std::size_t & ) other._numOfColumns , ( std::size_t && ) 0 ) ) ,
              _data ( std::exchange < T * > ( ( T *& ) other._data , nullptr ) ) //Move Constructor
    {
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator = ( const Matrix < T > &rhs ) // Copy Assignment
    {
        if ( this == &rhs )
        {
            return *this;
        }
        Matrix < T > temp ( rhs );
        Matrix < T >::swap ( ( Matrix < T > & ) *this , ( Matrix < T > & ) temp );
        return *this;
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator = ( Matrix < T > &&rhs ) noexcept // Move Assignment
    {
        this->_numOfRows = std::exchange ( rhs._numOfRows , 0 );
        this->_numOfColumns = std::exchange ( rhs._numOfColumns , 0 );
        this->_data = std::exchange ( rhs._data , nullptr );
        return *this;
    }
    template < class T >
    Matrix < T >::~Matrix () //Destructor
    {
        this->_numOfRows = 0;
        this->_numOfColumns = 0;
        delete[] this->_data;
    }
    template < class T >
    std::size_t Matrix < T >::numOfRows () const
    {
        return this->_numOfRows;
    }
    template < class T >
    std::size_t Matrix < T >::numOfColumns () const
    {
        return this->_numOfColumns;
    }
    template < class T >
    std::size_t Matrix < T >::numOfElements () const
    {
        return this->_numOfRows * this->_numOfColumns;
    }
    template < class T >
    void Matrix < T >::fill ( T value )
    {
        for ( std::size_t i = 0; i < this->_numOfRows; i++ )
        {
            for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
            {
                this->_data[ i * this->_numOfColumns + j ] = value;
            }
        }
    }
    template < class T >
    T &Matrix < T >::at ( std::size_t i , std::size_t j )
    {
        return this->_data[ ( ( i - 1 ) * this->_numOfColumns ) + ( j - 1 ) ];
    }
    template < class T >
    T &Matrix < T >::operator () ( std::size_t i , std::size_t j )
    {
        return this->at ( i , j );
    }
    template < class T >
    T Matrix < T >::getElement ( std::size_t i , std::size_t j ) const
    {
        this->checkBounds ( i , j );
        return this->getElementInner ( i , j );
    }
    template < class T >
    std::vector < T > Matrix < T >::operator [] ( std::size_t i )
    {
        size_t rowIndex = i - 1;
        return std::vector < T > ( &_data[ rowIndex * _numOfColumns ] , &_data[ rowIndex * _numOfColumns + _numOfColumns ] );
    }
    template < class T >
    bool Matrix < T >::isSquare () const
    {
        return _numOfRows != _numOfColumns;
    }
    template < class T >
    bool Matrix < T >::isVector () const
    {
        return _numOfRows == 1;
    }
    template < class T >
    bool Matrix < T >::isColumn () const
    {
        return _numOfColumns == 1;
    }
    template < class T >
    bool Matrix < T >::isUpperTri () const
    {
        if ( !this->isSquare () )
        {
            return false;
        }
        for ( std::size_t i = 2; i <= this->_numOfRows; ++i )
        {
            for ( std::size_t j = 1; j < i; j++ )
            {
                if ( std::fabs ( this->getElementInner ( i , j ) ) > std::numeric_limits < T >::epsilon () )
                {
                    return false;
                }
            }
        }
        return true;
    }
    template < class T >
    bool Matrix < T >::isLowerTri () const
    {
        if ( !this->isSquare () )
        {
            return false;
        }
        for ( std::size_t i = 1; i <= this->_numOfRows - 1; ++i )
        {
            for ( std::size_t j = i + 1; j <= this->_numOfColumns; j++ )
            {
                if ( std::fabs ( this->getElementInner ( i , j ) ) > std::numeric_limits < T >::epsilon () )
                {
                    return false;
                }
            }
        }
        return true;
    }
    template < class T >
    bool Matrix < T >::isDiagonal () const
    {
        return this->isUpperTri () && this->isLowerTri ();
    }
    template < class T >
    bool Matrix < T >::isSymmetric () const
    {
        if ( !this->isSquare () )
        {
            return false;
        }
        for ( int i = 1; i <= this->_numOfRows; ++i )
        {
            for ( int j = i + 1; j <= this->_numOfColumns; ++j )
            {
            }
        }
        return true;
    }
    template < class T >
    std::vector < T > Matrix < T >::row ( std::size_t i ) const
    {
        std::vector < T > result ( _numOfColumns );
        const std::size_t startIndex = ( i - 1 ) * _numOfColumns;
        const std::size_t endIndex = startIndex + _numOfColumns;
        for ( std::size_t index = startIndex; index < endIndex; index++ )
        {
            result.push_back ( _data[ index ] );
        }
        return result;
    }
    template < class T >
    std::vector < T > Matrix < T >::column ( std::size_t j ) const
    {
        std::vector < T > result ( this->_numOfRows );
        for ( int i = 0; i < this->_numOfRows; ++i )
        {
            result[ i ] ( this->getElementInner ( i + 1 , j ) );
        }
        return result;
    }
    template < class T >
    std::vector < T > Matrix < T >::diag () const
    {
        if ( this->isSquare () )
        {
            throw std::invalid_argument ( "The matrix must be a square matrix" );
        }
        std::vector < T > result ( this->_numOfRows );
        for ( std::size_t i = 0; i < this->_numOfRows; i++ )
        {
            result[ i ] = this->getElementInner ( i + 1 , i + 1 );
        }
        return result;
    }
    template < class T >
    void Matrix < T >::transpose ()
    {
        for ( std::size_t start = 0; start <= this->_numOfColumns * this->_numOfRows - 1; ++start )
        {
            std::size_t next = start;
            std::size_t i = 0;
            do
            {
                ++i;
                next = ( next % this->_numOfRows ) * this->_numOfColumns + next / this->_numOfRows;
            }
            while ( next > start );
            if ( next >= start && i != 1 )
            {
                const T tmp = this->_data[ start ];
                next = start;
                do
                {
                    i = ( next % this->_numOfRows ) * this->_numOfColumns + next / this->_numOfRows;
                    this->_data[ next ] = ( i == start ) ? tmp : this->_data[ i ];
                    next = i;
                }
                while ( next > start );
            }
        }
        std::swap ( ( std::size_t & ) this->_numOfRows , ( std::size_t & ) this->_numOfColumns );
    }
    template < class T >
    void Matrix < T >::swapRows ( std::size_t i1 , std::size_t i2 )
    {
        for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
        {
            const size_t i1Index = i1 * this->_numOfColumns + j;
            const size_t i2Index = i2 * this->_numOfColumns + j;
            std::swap ( ( T & ) this->_data[ i1Index ] , ( T & ) this->_data[ i2Index ] );
        }
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator += ( const Matrix < T > &right )
    {
        if ( this->_numOfRows != right._numOfRows || this->_numOfColumns != right._numOfRows )
        {
            throw std::invalid_argument ( "The 2 matrices must be of the same size" );
        }
        for ( std::size_t i = 1; i <= this->_numOfRows; i++ )
        {
            for ( std::size_t j = 1; j <= this->_numOfColumns; j++ )
            {
                T &toModify = this->at ( i , j );
                toModify = toModify + right.getElementInner ( i , j );
            }
        }
        return *this;
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator -= ( const Matrix < T > &right )
    {
        if ( this->_numOfRows != right._numOfRows || this->_numOfColumns != right._numOfRows )
        {
            throw std::invalid_argument ( "The 2 matrices must be of the same size" );
        }
        for ( std::size_t i = 1; i <= this->_numOfRows; i++ )
        {
            for ( std::size_t j = 1; j <= this->_numOfColumns; j++ )
            {
                T &toModify = this->at ( i , j );
                toModify = toModify - right.getElementInner ( i , j );
            }
        }
        return *this;
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator *= ( const Matrix < T > &right )
    {
        if ( this->_numOfColumns != right._numOfRows )
        {
            throw std::invalid_argument ( "The number of columns of the left matrix must be equal to the number of row of the right matrix." );
        }
        Matrix temp ( this->_numOfRows , right._numOfColumns );
        for ( int i = 1; i <= temp._numOfRows; ++i )
        {
            for ( int j = 1; j <= temp._numOfColumns; ++j )
            {
                for ( int k = 1; k <= this->_numOfColumns; ++k )
                {
                    temp.at ( i , j ) += ( this->at ( i , k ) * right.getElementInner ( k , j ) );
                }
            }
        }
        return ( *this = temp );
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator *= ( const T &right )
    {
        for ( int i = 1; i <= this->_numOfRows; ++i )
        {
            for ( int j = 1; j <= this->_numOfColumns; ++j )
            {
                this->at ( i , j ) *= right;
            }
        }
        return *this;
    }
    template < class T >
    Matrix < T > &Matrix < T >::operator /= ( const T &right )
    {
        for ( int i = 1; i <= this->_numOfRows; ++i )
        {
            for ( int j = 1; j <= this->_numOfColumns; ++j )
            {
                this->at ( i , j ) /= right;
            }
        }
        return *this;
    }
    template < class T >
    void Matrix < T >::each ( std::function < T ( T ) > func )
    {
        for ( std::size_t i = 1; i <= this->_numOfRows; i++ )
        {
            for ( std::size_t j = 1; j <= this->_numOfColumns; j++ )
            {
                T &toModify = this->at ( i , j );
                toModify = func ( toModify );
            }
        }
    }
    template < class T >
    Matrix < T > operator + ( const Matrix < T > &left , const Matrix < T > &right )
    {
        Matrix < T > temp ( left );
        return ( temp += right );
    }
    template < class T >
    Matrix < T > operator - ( const Matrix < T > &left , const Matrix < T > &right )
    {
        Matrix < T > temp ( left );
        return ( temp -= right );
    }
    template < class T >
    Matrix < T > operator * ( const Matrix < T > &left , const Matrix < T > &right )
    {
        Matrix < T > temp ( left );
        return ( temp *= right );
    }
    template < class T >
    Matrix < T > operator * ( const Matrix < T > &left , const T &right )
    {
        Matrix < T > temp ( left );
        return ( temp *= right );
    }
    template < class T >
    Matrix < T > operator * ( const T &left , const Matrix < T > &right )
    {
        return ( right * left );
    }
    template < class T >
    Matrix < T > operator / ( const Matrix < T > &left , const T &right )
    {
        Matrix < T > temp ( left );
        return ( temp /= right );
    }
}
#endif //MATRIXLIB_MATRIX_H
