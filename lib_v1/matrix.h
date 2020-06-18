#pragma once

#include <malloc.h>
#include <stdexcept>
#include <ostream>
#include <initializer_list>
#include <string>

#include "matrix_iter.cpp"

namespace ml
{
    template <class typ>
    class matrix {
    private:
        typ* m;
        size_t w, h, s;
    public:
        matrix();
        matrix(const std::initializer_list<std::initializer_list<typ>> data);
        matrix(const size_t width, const size_t height);
        matrix(matrix<typ>&& other);
        matrix(const matrix<typ>& other);
        const typ& at(const size_t x, const size_t y) const;
        typ& at(const size_t x, const size_t y);
        matrix_iterator<typ> begin();
        matrix_iterator<typ> end();
        const_matrix_iterator<typ> begin() const;
        const_matrix_iterator<typ> end() const;
        typ* data();
        typ const * data() const;
        const size_t& width() const;
        const size_t& height() const;
        const size_t& size() const;
        void fill(const typ& val);
        void swap(matrix<typ>& other);
        matrix<typ> t();
        ~matrix();

        template <class t>
        friend std::ostream& operator<<(std::ostream& stream, const matrix<t>& ma);

        template <class t>
        friend void swap(matrix<t>& ma0, matrix<t>& ma1);

        template <class to, class from>
        friend matrix<to> matrix_cast(matrix<from>& toCast);

        template <class t, class o>
        friend matrix<t> operator+(const matrix<t>& ma, const o& val);

        template <class t>
        friend matrix<t> operator+(const matrix<t>& ma0, const matrix<t>& ma1);

        template <class t, class o>
        friend matrix<t> operator-(const matrix<t>& ma, const o& val);

        template <class t>
        friend matrix<t> operator-(const matrix<t>& ma0, const matrix<t>& ma1);

        template <class t, class o>
        friend matrix<t> operator*(const matrix<t>& ma, const o& val);

        template <class t>
        friend matrix<t> operator*(const matrix<t>& ma0, const matrix<t>& ma1);

        template <class t, class o>
        friend matrix<t> operator/(const matrix<t>& ma, const o& val);

        template <class t>
        friend matrix<t> operator/(const matrix<t>& ma0, const matrix<t>& ma1);

        template <class t>
        friend matrix<t> operator%(const matrix<t>& ma0, const matrix<t>& ma1);

        typ& operator()(const size_t x, const size_t y);
        void operator=(const matrix<typ>& other);
        const typ& operator()(const size_t x, const size_t y) const;
        
        template <class o>
        matrix<typ>& operator+=(const o& val);
        
        template <class o>
        matrix<typ>& operator+=(const matrix<o>& other);
        
        template <class o>
        matrix<typ>& operator-=(const o& val);
        
        template <class o>
        matrix<typ>& operator-=(const matrix<o>& other);
        
        template <class o>
        matrix<typ>& operator*=(const o& val);
        
        template <class o>
        matrix<typ>& operator*=(const matrix<o>& other);
        
        template <class o>
        matrix<typ>& operator/=(const o& val);
        
        template <class o>
        matrix<typ>& operator/=(const matrix<o>& other);
    }; 

    template <class t>
    std::ostream& operator<<(std::ostream& stream, const matrix<t>& ma);

    template <class t>
    void swap(matrix<t>& ma0, matrix<t>& ma1);

    template <class to, class from>
    matrix<to> matrix_cast(matrix<from>& toCast);

    template <class t, class o>
    matrix<t> operator+(const matrix<t>& ma, const o& val);

    template <class t>
    matrix<t> operator+(const matrix<t>& ma0, const matrix<t>& ma1);

    template <class t, class o>
    matrix<t> operator-(const matrix<t>& ma, const o& val);

    template <class t>
    matrix<t> operator-(const matrix<t>& ma0, const matrix<t>& ma1);

    template <class t, class o>
    matrix<t> operator*(const matrix<t>& ma, const o& val);

    template <class t>
    matrix<t> operator*(const matrix<t>& ma0, const matrix<t>& ma1);

    template <class t, class o>
    matrix<t> operator/(const matrix<t>& ma, const o& val);

    template <class t>
    matrix<t> operator/(const matrix<t>& ma0, const matrix<t>& ma1);

    template <class t>
    matrix<t> operator%(const matrix<t>& ma0, const matrix<t>& ma1);
}