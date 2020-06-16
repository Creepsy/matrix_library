#pragma once

#include <iterator>

namespace ml
{
    template <class typ>
    class matrix_iterator : public std::iterator<std::random_access_iterator_tag, typ, size_t, typ*, typ&>
    {
    private:
        typ* curr;
    public:
        matrix_iterator() : curr(nullptr) {}
        matrix_iterator(typ* start) : curr(start) {}

        bool operator==(const matrix_iterator<typ>& other) const {
            return this -> curr == other.curr;
        }

        bool operator!=(const matrix_iterator<typ>& other) const {
            return !(*this == other);
        }

        bool operator>(const matrix_iterator<typ>& other) const {
            return this -> curr > other.curr;
        }

        bool operator<(const matrix_iterator<typ>& other) const {
            return this -> curr < other.curr;
        }

        bool operator>=(const matrix_iterator<typ>& other) const {
            return (*this > other || *this == other);
        }

        bool operator<=(const matrix_iterator<typ>& other) const {
            return (*this < other || *this == other);
        }

        typ& operator*() {
            return *this -> curr;
        }

        matrix_iterator<typ>& operator++() {
            this -> curr++;
            return *this;
        }

        matrix_iterator<typ> operator++(int) {
            matrix_iterator<typ> ret = *this;
            ++*this;
            return ret;
        }

        matrix_iterator<typ>& operator--() {
            this -> curr--;
            return *this;
        }

        matrix_iterator<typ> operator--(int) {
            matrix_iterator<typ> ret = *this;
            --*this;
            return ret;
        }

        matrix_iterator<typ> operator-(const matrix_iterator<typ>& other) const {
            matrix_iterator<typ> ret = *this;
            ret -= other;
            return ret;
        }

        matrix_iterator<typ> operator+(const matrix_iterator<typ>& other) const {
            matrix_iterator<typ> ret = *this;
            ret += other;
            return ret;
        }

        matrix_iterator<typ> operator-(const int val) const {
            matrix_iterator<typ> ret = *this;
            ret -= val;
            return ret;  
        }

        matrix_iterator<typ> operator+(const int val) const {
            matrix_iterator<typ> ret = *this;
            ret += val;
            return ret;
        }

        matrix_iterator<typ>& operator-=(const matrix_iterator<typ>& other){
            this -> curr -= other.curr;
            return *this;
        }

        matrix_iterator<typ>& operator+=(const matrix_iterator<typ>& other){
            this -> curr += other.curr;
            return *this;
        }

        matrix_iterator<typ>& operator-=(const int val){
            this -> curr -= val;
            return *this;  
        }

        matrix_iterator<typ>& operator+=(const int val){
            this -> curr += val;
            return *this;
        }

        typ& operator[](size_t i) {
            return this -> curr[i];
        }

        ~matrix_iterator() {}
    };

    template <class typ>
    class const_matrix_iterator : public std::iterator<std::random_access_iterator_tag, const typ, size_t, typ const*, const typ&>
    {
    private:
        typ const * curr;
    public:
        const_matrix_iterator() : curr(nullptr) {}
        const_matrix_iterator(typ const * start) : curr(start) {}

        bool operator==(const const_matrix_iterator<typ>& other) const {
            return this -> curr == other.curr;
        }

        bool operator!=(const const_matrix_iterator<typ>& other) const {
            return !(*this == other);
        }

        bool operator>(const const_matrix_iterator<typ>& other) const {
            return this -> curr > other.curr;
        }

        bool operator<(const const_matrix_iterator<typ>& other) const {
            return this -> curr < other.curr;
        }

        bool operator>=(const const_matrix_iterator<typ>& other) const {
            return (*this > other || *this == other);
        }

        bool operator<=(const const_matrix_iterator<typ>& other) const {
            return (*this < other || *this == other);
        }

        const typ& operator*() const {
            return *this -> curr;
        }

        const_matrix_iterator<typ>& operator++() {
            this -> curr++;
            return *this;
        }

        const_matrix_iterator<typ> operator++(int) {
            const_matrix_iterator<typ> ret = *this;
            ++*this;
            return ret;
        }

        const_matrix_iterator<typ>& operator--() {
            this -> curr--;
            return *this;
        }

        const_matrix_iterator<typ> operator--(int) {
            const_matrix_iterator<typ> ret = *this;
            --*this;
            return ret;
        }

        const_matrix_iterator<typ> operator-(const const_matrix_iterator<typ>& other) const {
            const_matrix_iterator<typ> ret = *this;
            ret -= other;
            return ret;
        }

        const_matrix_iterator<typ> operator+(const const_matrix_iterator<typ>& other) const {
            const_matrix_iterator<typ> ret = *this;
            ret += other;
            return ret;
        }

        const_matrix_iterator<typ> operator-(const int val) const {
            const_matrix_iterator<typ> ret = *this;
            ret -= val;
            return ret;  
        }

        const_matrix_iterator<typ> operator+(const int val) const {
            const_matrix_iterator<typ> ret = *this;
            ret += val;
            return ret;
        }

        const_matrix_iterator<typ>& operator-=(const const_matrix_iterator<typ>& other){
            this -> curr -= other.curr;
            return *this;
        }

        const_matrix_iterator<typ>& operator+=(const const_matrix_iterator<typ>& other){
            this -> curr += other.curr;
            return *this;
        }

        const_matrix_iterator<typ>& operator-=(const int val){
            this -> curr -= val;
            return *this;  
        }

        const_matrix_iterator<typ>& operator+=(const int val){
            this -> curr += val;
            return *this;
        }

        const typ& operator[](size_t i) const {
            return this -> curr[i];
        }

        ~const_matrix_iterator() {}
    };
}
