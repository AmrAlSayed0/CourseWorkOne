#ifndef COURSEWORKONE_MATRIX_H
#define COURSEWORKONE_MATRIX_H
#include <cstddef>
#include <utility>
#include <functional>
#include <limits>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <cmath>
namespace Core
{
    /**
     * @brief Represents a matrix of arbitrary size.
     * @tparam T A floating point type to be used for calculations.
     */
    template < class T >
    class Matrix
    {
    private:
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
        void fixSizeIfZero ()
        {
            if ( this->_numOfRows == 0 || this->_numOfColumns == 0 )
            {
                this->_numOfRows = 0;
                this->_numOfColumns = 0;
            }
        }
        /**
         * @brief Checks if the given numbers are within the bounds of the matrix and throws an std::out_of_bounds exception if it is not
         * @param i The row number to check
         * @param j The column number to check
         */
        void checkBounds ( std::size_t i , std::size_t j ) const
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
        /**
         * @brief Gets the element at the specified row and column but without a bounds check
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return The element at row i and column j.
         */
        T getElementInner ( std::size_t i , std::size_t j ) const
        {
            return this->_data[ ( ( i - 1 ) * this->_numOfColumns ) + ( j - 1 ) ];
        }
        /**
         * @brief Allocates the required memory.
         */
        void allocate ()
        {
            if ( this->_data != nullptr )
            {
                delete[] this->_data;
                this->_data = nullptr;
            }
            this->_data = new T[this->_numOfRows * this->_numOfColumns];
        }
    public:
        using ElementType = T;
        /**
         * @brief Creates an identity matrix with the specified size.
         * @param numOfRowsOrColumns The size of the matrix, both width and height.
         * @return
         */
        static Matrix < T > identity ( std::size_t numOfRowsOrColumns )
        {
            Matrix < T > identityResult ( numOfRowsOrColumns , numOfRowsOrColumns , static_cast < const T > ( 0 ) );
            for ( std::size_t i = 1; i <= identityResult._numOfRows; ++i )
            {
                identityResult ( i , i ) = 1;
            }
            return identityResult;
        }
        /**
         * @brief Augments the second matrix on to the first one and returns a new matrix. Both matrices must have the same number of rows.
         * @param augmentedTo The matrix to augment to.
         * @param augmentedBy The matrix to augment with.
         * @return A new matrix that is the result of the augmentation.
         */
        static Matrix < T > augment ( const Matrix < T > & augmentedTo , const Matrix < T > & augmentedBy )
        {
            if ( augmentedTo._numOfRows != augmentedBy._numOfRows )
            {
                throw std::invalid_argument ( "The augmented matrix must have the same number of rows as the matrix to augment with." );
            }
            Matrix augmented ( augmentedTo._numOfRows , augmentedTo._numOfColumns + augmentedBy._numOfColumns );
            for ( std::size_t i = 1; i <= augmented._numOfRows; ++i )
            {
                for ( std::size_t j = 1; j <= augmented._numOfColumns; ++j )
                {
                    if ( j <= augmentedTo._numOfColumns )
                    {
                        augmented ( i , j ) = augmentedTo.getElementInner ( i , j );
                    }
                    else
                    {
                        augmented ( i , j ) = augmentedBy.getElementInner ( i , j - augmentedTo._numOfColumns );
                    }
                }
            }
            return augmented;
        }
        /**
         * @brief Constructs a 0 x 0 matrix.
         */
        Matrix ()
            : Matrix ( static_cast < const std::size_t > ( 0 ) , static_cast < const std::size_t > ( 0 ) )
        {
        }
        /**
         * @brief Constructs a matrix of the desired size and zeros it out.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         */
        Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns )
            : Matrix ( numOfRows , numOfColumns , static_cast < T const > ( 0 ) )
        {
        }
        /**
         * @brief Constructs a matrix of the desired size and fills all the cells with the provided value.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         * @param value The value that the matrix should be filled with.
         */
        Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns , T const value )
            : _numOfRows ( numOfRows ) ,
              _numOfColumns ( numOfColumns )
        {
            this->fixSizeIfZero ();
            this->allocate ();
            this->fill ( value );
        }
        /**
         * @brief Constructs a matrix of the desired size and fills all the cells with the provided data.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         * @param data The data that the matrix should be filled with. This must be in the form of a contiguous array of values. Must be at least numOfRows * numOfColumns long.
         */
        Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns , T const * const data )
            : _numOfRows ( numOfRows ) ,
              _numOfColumns ( numOfColumns )
        {
            this->fixSizeIfZero ();
            this->allocate ();
            for ( std::size_t i = 0; i < this->_numOfRows; i++ )
            {
                for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
                {
                    this->at ( i + 1 , j + 1 ) = data[ ( i * this->_numOfColumns ) + j ];
                }
            }
        }
        /**
         * @brief Constructs a matrix of the desired size and fills all the cells with the provided data.
         * @param numOfRows The number of rows the matrix should be.
         * @param numOfColumns The number of columns the matrix should be.
         * @param data he data that the matrix should be filled with. This must be in the form of an array of arrays. The outer array must be of length numOfRows and each of the inner arrays must be numOfColumns long.
         */
        Matrix ( const std::size_t numOfRows , const std::size_t numOfColumns , T const * const * const data )
            : _numOfRows ( numOfRows ) ,
              _numOfColumns ( numOfColumns )
        {
            this->fixSizeIfZero ();
            for ( std::size_t i = 0; i < this->_numOfRows; i++ )
            {
                for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
                {
                    this->at ( i + 1 , j + 1 ) = data[ i ][ j ];
                }
            }
        }
        /**
         * @brief Copies the provided matrix into this one.
         * @param other The matrix to copy.
         */
        Matrix ( const Matrix < T > & other )
            : _numOfRows ( other._numOfRows ) ,
              _numOfColumns ( other._numOfColumns ) ,
              _data ( new T[other._numOfRows * other._numOfColumns] ) //Copy Constructor
        {
            std::memcpy ( static_cast < void * > ( this->_data ) , static_cast < const void * > ( other._data ) , this->_numOfRows * this->_numOfColumns * sizeof ( T ) );
        }
        /**
         * @brief Moves the provided matrix into this one. The other matrix is no longer usable.
         * @param other The matrix to move.
         */
        Matrix ( Matrix < T > && other ) noexcept
            : _numOfRows ( std::exchange ( ( std::size_t & ) other._numOfRows , static_cast < std::size_t && > ( 0 ) ) ) ,
              _numOfColumns ( std::exchange ( ( std::size_t & ) other._numOfColumns , static_cast < std::size_t && > ( 0 ) ) ) ,
              _data ( std::exchange ( static_cast < T *& > ( other._data ) , static_cast < T *&& > ( nullptr ) ) ) //Move Constructor
        {
        }
        /**
         * @brief Cleans the matrix and de-allocates the storage.
         */
        ~Matrix () //Destructor
        {
            this->_numOfRows = 0;
            this->_numOfColumns = 0;
            if ( this->_data != nullptr )
            {
                delete[] this->_data;
            }
        }
        /**
         * @brief Copies the right matrix into the left one.
         * @param rhs The rhs matrix that should be copied into this one.
         * @return A reference to the new copied into matrix
         */
        Matrix < T > & operator = ( const Matrix < T > & rhs ) // Copy Assignment
        {
            if ( this == &rhs )
            {
                return *this;
            }
            this->_numOfRows = rhs._numOfRows;
            this->_numOfColumns = rhs._numOfColumns;
            this->allocate ();
            std::memcpy ( static_cast < void * > ( rhs._data ) , static_cast < const void * > ( this->_data ) , rhs._numOfRows * rhs._numOfColumns * sizeof ( T ) );
            return *this;
        }
        /**
         * @brief Moves the right matrix into the left one. The right matrix is no longer usable after the assignment.
         * @param rhs The other matrix that should be moved into this one.
         * @return A reference to the new moved into matrix
         */
        Matrix < T > & operator = ( Matrix < T > && rhs ) noexcept // Move Assignment
        {
            this->_numOfRows = std::exchange ( ( std::size_t & ) rhs._numOfRows , static_cast < std::size_t && > ( 0 ) );
            this->_numOfColumns = std::exchange ( ( std::size_t & ) rhs._numOfColumns , static_cast < std::size_t && > ( 0 ) );
            if ( this->_data != nullptr )
            {
                delete[] this->_data;
            }
            this->_data = std::exchange ( ( T *& ) rhs._data , static_cast < T *&& > ( nullptr ) );
            return *this;
        }
        /**
         * @brief Gets the number of rows in the matrix.
         * @return The number of rows in the matrix.
         */
        [[nodiscard]]
        std::size_t numOfRows () const
        {
            return this->_numOfRows;
        }
        /**
         * @brief Gets the number of columns in the matrix.
         * @return The number of columns in the matrix.
         */
        [[nodiscard]]
        std::size_t numOfColumns () const
        {
            return this->_numOfColumns;
        }
        /**
         * @brief Get the total number of elements in the matrix.
         * @return The total number of elements in the matrix
         */
        [[nodiscard]]
        std::size_t numOfElements () const
        {
            return this->_numOfRows * this->_numOfColumns;
        }
        /**
         * @brief Fills the entire matrix with the given value.
         * @param value The value to fill the matrix with
         */
        void fill ( T value )
        {
            size_t numOfElements = this->_numOfRows * this->_numOfColumns;
            for ( std::size_t i = 0; i < numOfElements; i++ )
            {
                this->_data[ i ] = value;
            }
        }
        /**
         * @brief Gets the element at the specified row and column. This method doesn't do any bounds checking.
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return The element at row i and column j.
         */
        T & at ( std::size_t i , std::size_t j )
        {
            return this->_data[ ( ( i - 1 ) * this->_numOfColumns ) + ( j - 1 ) ];
        }
        /**
         * @brief Gets the element at the specified row and column. This method doesn't do any bounds checking. It returns an lvalue reference so it can be assigned directly.
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return A reference to the element at row i and column j.
         */
        T & operator () ( std::size_t i , std::size_t j )
        {
            return this->at ( i , j );
        }
        /**
         * @brief Gets the element at the specified row and column. This method does bound checking and throws std::out_of_range exception if i or j is out of bounds.
         * @param i The row number the element is at. Starting at 1.
         * @param j The column number the element is at. Starting at 1.
         * @return The element at row i and column j.
         */
        T getElement ( std::size_t i , std::size_t j ) const
        {
            this->checkBounds ( i , j );
            return this->getElementInner ( i , j );
        }
        /**
         * @brief Gets the row of the specified number as a vector.
         * @param i The row number to get.
         * @return The specified row as a vector.
         */
        std::vector < T > operator [] ( std::size_t i )
        {
            size_t rowIndex = i - 1;
            return std::vector < T > ( &this->_data[ rowIndex * this->_numOfColumns ] , &this->_data[ rowIndex * this->_numOfColumns + this->_numOfColumns ] );
        }
        /**
         * @brief Checks if the matrix is a square matrix i.e m = n.
         * @return Whether the matrix is square or not.
         */
        [[nodiscard]]
        bool isSquare () const
        {
            return this->_numOfRows == this->_numOfColumns;
        }
        /**
         * @brief Checks if the matrix is a vector i.e only one row.
         * @return Whether the matrix is a vector or not.
         */
        [[nodiscard]]
        bool isVector () const
        {
            return this->_numOfRows == 1;
        }
        /**
         * @brief Checks if the matrix is a column i.e only one column
         * @return
         */
        [[nodiscard]]
        bool isColumn () const
        {
            return this->_numOfColumns == 1;
        }
        /**
         * @brief Checks if the matrix elements only in the upper triangle.
         * @return Whether the matrix is upper triangle. Also returns false for non-square matrices.
         */
        [[nodiscard]]
        bool isUpperTri () const
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
        /**
         * @brief Checks if the matrix elements only in the lower triangle.
         * @return Whether the matrix is lower triangle. Also returns false for non-square matrices.
         */
        [[nodiscard]]
        bool isLowerTri () const
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
        /**
         * @brief Checks if the matrix elements only in the diagonal.
         * @return Whether the matrix is diagonal. Also returns false for non-square matrices.
         */
        [[nodiscard]]
        bool isDiagonal () const
        {
            return this->isUpperTri () && this->isLowerTri ();
        }
        /**
         * @brief Checks if the matrix is symmetrical i.e a ( i , j ) = a ( j , i ) for all values of i and j.
         * @return Whether the matrix is symmetrical. Also returns false for non-square matrices.
         */
        [[nodiscard]]
        bool isSymmetric () const
        {
            if ( !this->isSquare () )
            {
                return false;
            }
            for ( std::size_t i = 1; i <= this->_numOfRows; ++i )
            {
                for ( std::size_t j = i + 1; j <= this->_numOfColumns; ++j )
                {
                    if ( std::fabs ( this->getElementInner ( i , j ) - this->getElementInner ( j , i ) ) > std::numeric_limits < T >::epsilon () )
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        /**
         * @brief Gets a copy of the specified row.
         * @param i The row number to get.
         * @return A copy of the specified row.
         */
        std::vector < T > row ( std::size_t i ) const
        {
            std::vector < T > result ( this->_numOfColumns );
            for ( std::size_t index = 0; index < this->_numOfRows; ++index )
            {
                result[ index ] = this->getElementInner ( i , index + 1 );
            }
            return result;
        }
        /**
         * @brief Gets a copy of the specified column.
         * @param j The column number to get.
         * @return A copy of the specified column.
         */
        std::vector < T > column ( std::size_t j ) const
        {
            std::vector < T > result ( this->_numOfRows );
            for ( std::size_t index = 0; index < this->_numOfRows; ++index )
            {
                result[ index ] = this->getElementInner ( index + 1 , j );
            }
            return result;
        }
        /**
         * @brief Gets a copy of the diagonal of the matrix. This throws std::invalid_argument exception if the matrix is not square.
         * @return A copy of the diagonal
         */
        std::vector < T > diag () const
        {
            if ( this->isSquare () )
            {
                throw std::invalid_argument ( "The matrix must be a square matrix" );
            }
            std::vector < T > result ( this->_numOfRows );
            for ( std::size_t index = 0; index < this->_numOfRows; index++ )
            {
                result[ index ] = this->getElementInner ( index + 1 , index + 1 );
            }
            return result;
        }
        /**
         * @brief Calculates the determinant of the matrix. Must be a square matrix.
         * @return The determinant of the matrix;
         */
        T determinant () const
        {
            if ( !this->isSquare () )
            {
                throw std::invalid_argument ( "Can't calculate the determinant of a non-square matrix" );
            }
            if ( this->_numOfRows == 0 )
            {
                return 0;
            }
            if ( this->_numOfRows == 1 )
            {
                return this->getElementInner ( 1 , 1 );
            }
            if ( this->_numOfRows == 2 )
            {
                return ( this->getElementInner ( 1 , 1 ) * this->getElementInner ( 2 , 2 ) ) - ( this->getElementInner ( 1 , 2 ) * this->getElementInner ( 2 , 1 ) );
            }

            //TODO: Implement for higher sizes.
            return 0;
        }
        /**
         * @brief Adds the right matrix to this one. Must be of the same size.
         * @param right The matrix to add.
         * @return The modified matrix.
         */
        Matrix < T > & operator += ( const Matrix < T > & right )
        {
            if ( this->_numOfRows != right._numOfRows || this->_numOfColumns != right._numOfRows )
            {
                throw std::invalid_argument ( "The 2 matrices must be of the same size" );
            }
            for ( std::size_t i = 1; i <= this->_numOfRows; i++ )
            {
                for ( std::size_t j = 1; j <= this->_numOfColumns; j++ )
                {
                    T & toModify = this->at ( i , j );
                    toModify = toModify + right.getElementInner ( i , j );
                }
            }
            return *this;
        }
        /**
         * @brief Subtracts the right matrix from this one. Must be of the same size.
         * @param right The matrix to subtract.
         * @return The modified matrix.
         */
        Matrix < T > & operator -= ( const Matrix < T > & right )
        {
            if ( this->_numOfRows != right._numOfRows || this->_numOfColumns != right._numOfRows )
            {
                throw std::invalid_argument ( "The 2 matrices must be of the same size" );
            }
            for ( std::size_t i = 1; i <= this->_numOfRows; i++ )
            {
                for ( std::size_t j = 1; j <= this->_numOfColumns; j++ )
                {
                    T & toModify = this->at ( i , j );
                    toModify = toModify - right.getElementInner ( i , j );
                }
            }
            return *this;
        }
        /**
         * @brief Multiplies the right matrix with this one. This is a dot multiplication operation not an element-wise operation. The number of columns of the left matrix must be equal to the number of rows of the right matrix.
         * @param right The matrix to multiply by.
         * @return The modified matrix.
         */
        Matrix < T > & operator *= ( const Matrix < T > & right )
        {
            if ( this->_numOfColumns != right._numOfRows )
            {
                throw std::invalid_argument ( "The number of columns of the left matrix must be equal to the number of row of the right matrix." );
            }
            Matrix temp ( this->_numOfRows , right._numOfColumns );
            for ( std::size_t i = 1; i <= temp._numOfRows; ++i )
            {
                for ( std::size_t j = 1; j <= temp._numOfColumns; ++j )
                {
                    for ( std::size_t k = 1; k <= this->_numOfColumns; ++k )
                    {
                        temp.at ( i , j ) += ( this->at ( i , k ) * right.getElementInner ( k , j ) );
                    }
                }
            }
            return ( *this = temp );
        }
        /**
         * @brief Multiplies each element of the matrix with the given value.
         * @param right The value to multiply each element with.
         * @return The multiplied matrix.
         */
        Matrix < T > & operator *= ( const T & right )
        {
            for ( std::size_t i = 1; i <= this->_numOfRows; ++i )
            {
                for ( std::size_t j = 1; j <= this->_numOfColumns; ++j )
                {
                    this->at ( i , j ) *= right;
                }
            }
            return *this;
        }
        /**
         * @brief Divides each element of the matrix with the given value.
         * @param right The value to divide by.
         * @return The divided matrix.
         */
        Matrix < T > & operator /= ( const T & right )
        {
            for ( std::size_t i = 1; i <= this->_numOfRows; ++i )
            {
                for ( std::size_t j = 1; j <= this->_numOfColumns; ++j )
                {
                    this->at ( i , j ) /= right;
                }
            }
            return *this;
        }
        /**
         * @brief Transposes the matrix in-place.
         */
        void transpose ()
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
        /**
         * @brief Swaps the locations of the 2 rows in the matrix
         * @param i1 The row number of the first row to swap.
         * @param i2 The row number of the second row to swap.
         */
        void swapRows ( std::size_t i1 , std::size_t i2 )
        {
            for ( std::size_t j = 0; j < this->_numOfColumns; j++ )
            {
                const size_t i1Index = ( i1 - 1 ) * this->_numOfColumns + j;
                const size_t i2Index = ( i2 - 1 ) * this->_numOfColumns + j;
                std::swap ( ( T & ) this->_data[ i1Index ] , ( T & ) this->_data[ i2Index ] );
            }
        }
        /**
         * @brief Transforms each element in the matrix using the provided function.
         * @param func The function to apply to each element.
         */
        void each ( const std::function < T ( T ) > & func )
        {
            for ( std::size_t i = 1; i <= this->_numOfRows; i++ )
            {
                for ( std::size_t j = 1; j <= this->_numOfColumns; j++ )
                {
                    T & toModify = this->at ( i , j );
                    toModify = func ( toModify );
                }
            }
        }
        /**
         * @brief Transforms each element in the specified row using the provided function.
         * @param i The row to apply the function on.
         * @param func The function to apply to each row element.
         */
        void eachInRow ( std::size_t i , const std::function < T ( T ) > & func )
        {
            for ( std::size_t j = 1; j <= this->_numOfColumns; ++j )
            {
                T & toModify = this->at ( i , j );
                toModify = func ( toModify );
            }
        }
        /**
         * @brief Transforms each element in the specified row using the provided function.
         * @param j The row to apply the function on.
         * @param func The function to apply to each row element.
         */
        void eachInColumn ( std::size_t j , const std::function < T ( T ) > & func )
        {
            for ( std::size_t i = 1; i <= this->_numOfRows; ++i )
            {
                T & toModify = this->at ( i , j );
                toModify = func ( toModify );
            }
        }
        /**
         * @brief Pivots the matrix around the element of the specified row and column. Only rows are swapped.
         * @param rowNum The row number of the row to switch with.
         * @param columnNum The column number to search for larger elements.
         * @return Whether a row has been switched.
         */
        bool pivotRow ( std::size_t rowNum , std::size_t columnNum )
        {
            /** Get a copy of the whole column we're searching */
            std::vector < T > column = this->column ( columnNum );
            /** Get the maximum element (ignoring sign) in the column but only from the rows under the row we're pivoting at */
            const auto searchBegin = column.begin () + rowNum;
            auto maxElementInColumn = std::max_element ( searchBegin , column.end () , [] ( T left , T right )
            {
                return std::fabs ( left ) < std::fabs ( right );
            } );
            /** If the maximum element is less than or equal to the element we're pivoting at, there is no need to pivot */
            if ( *maxElementInColumn <= this->getElementInner ( rowNum , columnNum ) )
            {
                return false;
            }
            auto maxElementInColumnIndex = maxElementInColumn - column.begin ();
            this->swapRows ( rowNum , static_cast < std::size_t > ( maxElementInColumnIndex  ) + 1 );
            return true;
        }
        /**
         * @brief Performs Gaussian elimination on the matrix using partial pivoting.
         */
        void eliminateUsingPartialPivoting ()
        {
            this->pivotRow ();
        }
        std::vector < T > eliminateUsingCompletePivoting ()
        {
        }
    };
}
namespace Core
{
    template < class T >
    Matrix < T > operator + ( const Matrix < T > & left , const Matrix < T > & right )
    {
        Matrix < T > temp ( left );
        return ( temp += right );
    }
    template < class T >
    Matrix < T > operator - ( const Matrix < T > & left , const Matrix < T > & right )
    {
        Matrix < T > temp ( left );
        return ( temp -= right );
    }
    template < class T >
    Matrix < T > operator * ( const Matrix < T > & left , const Matrix < T > & right )
    {
        Matrix < T > temp ( left );
        return ( temp *= right );
    }
    template < class T >
    Matrix < T > operator * ( const Matrix < T > & left , const T & right )
    {
        Matrix < T > temp ( left );
        return ( temp *= right );
    }
    template < class T >
    Matrix < T > operator * ( const T & left , const Matrix < T > & right )
    {
        return ( right * left );
    }
    template < class T >
    Matrix < T > operator / ( const Matrix < T > & left , const T & right )
    {
        Matrix < T > temp ( left );
        return ( temp /= right );
    }
}
#endif //COURSEWORKONE_MATRIX_H
