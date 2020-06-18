#pragma once

#include <iterator>

namespace ml
{
    template <class typ>
    class matrix_iterator : public std::iterator<std::random_access_iterator_tag, typ, size_t, typ*, typ&> {
    private:
        typ* curr;
    public:
        matrix_iterator();
        matrix_iterator(typ* start);

        bool operator==(const matrix_iterator<typ>& other) const;
        bool operator!=(const matrix_iterator<typ>& other) const;
        bool operator>(const matrix_iterator<typ>& other) const;
        bool operator<(const matrix_iterator<typ>& other) const;
        bool operator>=(const matrix_iterator<typ>& other) const;
        bool operator<=(const matrix_iterator<typ>& other) const;

        typ& operator*();

        matrix_iterator<typ>& operator++();
        matrix_iterator<typ> operator++(int);
        matrix_iterator<typ>& operator--();
        matrix_iterator<typ> operator--(int);

        matrix_iterator<typ> operator-(const matrix_iterator<typ>& other) const;
        matrix_iterator<typ> operator+(const matrix_iterator<typ>& other) const;
        matrix_iterator<typ> operator-(const int val) const;
        matrix_iterator<typ> operator+(const int val) const;
        
        matrix_iterator<typ>& operator-=(const matrix_iterator<typ>& other);
        matrix_iterator<typ>& operator+=(const matrix_iterator<typ>& other);
        matrix_iterator<typ>& operator-=(const int val);
        matrix_iterator<typ>& operator+=(const int val);

        typ& operator[](size_t i);

        ~matrix_iterator();
    };

    template <class typ>
    class const_matrix_iterator : public std::iterator<std::random_access_iterator_tag, const typ, size_t, typ const*, const typ&>
    {
    private:
        typ const * curr;
    public:
        const_matrix_iterator();
        const_matrix_iterator(typ const * start);

        bool operator==(const const_matrix_iterator<typ>& other) const;
        bool operator!=(const const_matrix_iterator<typ>& other) const;
        bool operator>(const const_matrix_iterator<typ>& other) const;
        bool operator<(const const_matrix_iterator<typ>& other) const;
        bool operator>=(const const_matrix_iterator<typ>& other) const; 
        bool operator<=(const const_matrix_iterator<typ>& other) const; 

        const typ& operator*() const;

        const_matrix_iterator<typ>& operator++();
        const_matrix_iterator<typ> operator++(int); 
        const_matrix_iterator<typ>& operator--();
        const_matrix_iterator<typ> operator--(int); 

        const_matrix_iterator<typ> operator-(const const_matrix_iterator<typ>& other) const;
        const_matrix_iterator<typ> operator+(const const_matrix_iterator<typ>& other) const;
        const_matrix_iterator<typ> operator-(const int val) const;
        const_matrix_iterator<typ> operator+(const int val) const;

        const_matrix_iterator<typ>& operator-=(const const_matrix_iterator<typ>& other);
        const_matrix_iterator<typ>& operator+=(const const_matrix_iterator<typ>& other);
        const_matrix_iterator<typ>& operator-=(const int val);
        const_matrix_iterator<typ>& operator+=(const int val);

        const typ& operator[](size_t i) const;
        ~const_matrix_iterator();
    };
}
