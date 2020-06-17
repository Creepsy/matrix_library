#include "matrix.h"

template<typename T>
extended::matrix<T>& extended::matrix<T>::operator+(const extended::matrix<T> &other) const
{
    if(data.size() != other.data.size() || rowSize != other.rowSize)
        throw std::runtime_error("diffrent ammount initialized or different size");

    extended::matrix<T> retVal(this->row_count(), this->row_size());

    for (size_t i = 0; i < data.size(); i++)
        retVal[i] = (*this)[i] + other[i];

    return retVal;
}

template<typename T>
extended::matrix<T>& extended::matrix<T>::operator-(const extended::matrix<T> &other) const
{
    if(data.size() != other.data.size() || rowSize != other.rowSize)
        throw std::runtime_error("diffrent ammount initialized or different size");

    extended::matrix<T> retVal(this->row_count(), this->row_size());

    for (size_t i = 0; i < data.size(); i++)
        retVal[i] = (*this)[i] - other[i];

    return retVal;
}

template<typename T>
extended::matrix<T>& extended::matrix<T>::operator*(const extended::matrix<T> & other) const
{
    if(this->rowSize != other.row_count())
        throw std::runtime_error("cannot multiply: this rowSize!= other rowCount");

    extended::matrix<T> retVal(other.rowSize, this->row_count());

    T vectorMultiplicationResult;

    for (size_t iRow = 0; iRow < row_count(); iRow++)
    {
        for(size_t iColumn = 0; iColumn < other.rowSize; iColumn++)
        {
            vectorMultiplicationResult = NULL;

            for(size_t i = 0; i < rowSize; i++)
                vectorMultiplicationResult += (*this)(iRow, i) * other(i, iColumn);

            retVal.data.push(vectorMultiplicationResult);
        }
    }
	
    return retVal;
}

template<typename T>
extended::matrix<T>& extended::matrix<T>::operator*(const T &scalar) const
{
    extended::matrix<T> retVal = (*this);

    for(auto i = retVal.data.begin(); i < retVal.data.end(); i++)
        *i *= scalar;
}