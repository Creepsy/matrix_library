#include "matrix_iter.h"

template <class typ>
ml::matrix_iterator<typ>::matrix_iterator() : curr(nullptr) {}

template <class typ>
ml::matrix_iterator<typ>::matrix_iterator(typ* start) : curr(start) {}

template <class typ>
bool ml::matrix_iterator<typ>::operator==(const matrix_iterator<typ>& other) const {
    return this -> curr == other.curr;
}

template <class typ>
bool ml::matrix_iterator<typ>::operator!=(const matrix_iterator<typ>& other) const {
    return !(*this == other);
}

template <class typ>
bool ml::matrix_iterator<typ>::operator>(const matrix_iterator<typ>& other) const {
    return this -> curr > other.curr;
}

template <class typ>
bool ml::matrix_iterator<typ>::operator<(const matrix_iterator<typ>& other) const {
    return this -> curr < other.curr;
}

template <class typ>
bool ml::matrix_iterator<typ>::operator>=(const matrix_iterator<typ>& other) const {
    return (*this > other || *this == other);
}

template <class typ>
bool ml::matrix_iterator<typ>::operator<=(const matrix_iterator<typ>& other) const {
    return (*this < other || *this == other);
}

template <class typ>
typ& ml::matrix_iterator<typ>::operator*() {
    return *this -> curr;
}

template <class typ>
ml::matrix_iterator<typ>& ml::matrix_iterator<typ>::operator++() {
    this -> curr++;
    return *this;
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix_iterator<typ>::operator++(int) {
    matrix_iterator<typ> ret = *this;
    ++*this;
    return ret;
}

template <class typ>
ml::matrix_iterator<typ>& ml::matrix_iterator<typ>::operator--() {
    this -> curr--;
    return *this;
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix_iterator<typ>::operator--(int) {
    matrix_iterator<typ> ret = *this;
    --*this;
    return ret;
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix_iterator<typ>::operator-(const matrix_iterator<typ>& other) const {
    matrix_iterator<typ> ret = *this;
    ret -= other;
    return ret;
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix_iterator<typ>::operator+(const matrix_iterator<typ>& other) const {
    matrix_iterator<typ> ret = *this;
    ret += other;
    return ret;
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix_iterator<typ>::operator-(const int val) const {
    matrix_iterator<typ> ret = *this;
    ret -= val;
    return ret;  
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix_iterator<typ>::operator+(const int val) const {
    matrix_iterator<typ> ret = *this;
    ret += val;
    return ret;
}

template <class typ>
ml::matrix_iterator<typ>& ml::matrix_iterator<typ>::operator-=(const matrix_iterator<typ>& other){
    this -> curr -= other.curr;
    return *this;
}

template <class typ>
ml::matrix_iterator<typ>& ml::matrix_iterator<typ>::operator+=(const matrix_iterator<typ>& other){
    this -> curr += other.curr;
    return *this;
}

template <class typ>
ml::matrix_iterator<typ>& ml::matrix_iterator<typ>::operator-=(const int val){
    this -> curr -= val;
    return *this;  
}

template <class typ>
ml::matrix_iterator<typ>& ml::matrix_iterator<typ>::operator+=(const int val){
    this -> curr += val;
    return *this;
}

template <class typ>
typ& ml::matrix_iterator<typ>::operator[](size_t i) {
    return this -> curr[i];
}

template <class typ>
ml::matrix_iterator<typ>::~matrix_iterator() {}




template <class typ>
ml::const_matrix_iterator<typ>::const_matrix_iterator() : curr(nullptr) {}

template <class typ>
ml::const_matrix_iterator<typ>::const_matrix_iterator(typ const * start) : curr(start) {}

template <class typ>
bool ml::const_matrix_iterator<typ>::operator==(const const_matrix_iterator<typ>& other) const {
    return this -> curr == other.curr;
}

template <class typ>
bool ml::const_matrix_iterator<typ>::operator!=(const const_matrix_iterator<typ>& other) const {
    return !(*this == other);
}

template <class typ>
bool ml::const_matrix_iterator<typ>::operator>(const const_matrix_iterator<typ>& other) const {
    return this -> curr > other.curr;
}

template <class typ>
bool ml::const_matrix_iterator<typ>::operator<(const const_matrix_iterator<typ>& other) const {
    return this -> curr < other.curr;
}

template <class typ>
bool ml::const_matrix_iterator<typ>::operator>=(const const_matrix_iterator<typ>& other) const {
    return (*this > other || *this == other);
}

template <class typ>
bool ml::const_matrix_iterator<typ>::operator<=(const const_matrix_iterator<typ>& other) const {
    return (*this < other || *this == other);
}

template <class typ>
const typ& ml::const_matrix_iterator<typ>::operator*() const {
    return *this -> curr;
}

template <class typ>
ml::const_matrix_iterator<typ>& ml::const_matrix_iterator<typ>::operator++() {
    this -> curr++;
    return *this;
}

template <class typ>
ml::const_matrix_iterator<typ> ml::const_matrix_iterator<typ>::operator++(int) {
    const_matrix_iterator<typ> ret = *this;
    ++*this;
    return ret;
}

template <class typ>
ml::const_matrix_iterator<typ>& ml::const_matrix_iterator<typ>::operator--() {
    this -> curr--;
    return *this;
}

template <class typ>
ml::const_matrix_iterator<typ> ml::const_matrix_iterator<typ>::operator--(int) {
    const_matrix_iterator<typ> ret = *this;
    --*this;
    return ret;
}

template <class typ>
ml::const_matrix_iterator<typ> ml::const_matrix_iterator<typ>::operator-(const const_matrix_iterator<typ>& other) const {
    const_matrix_iterator<typ> ret = *this;
    ret -= other;
    return ret;
}

template <class typ>
ml::const_matrix_iterator<typ> ml::const_matrix_iterator<typ>::operator+(const const_matrix_iterator<typ>& other) const {
    const_matrix_iterator<typ> ret = *this;
    ret += other;
    return ret;
}

template <class typ>
ml::const_matrix_iterator<typ> ml::const_matrix_iterator<typ>::operator-(const int val) const {
    const_matrix_iterator<typ> ret = *this;
    ret -= val;
    return ret;  
}

template <class typ>
ml::const_matrix_iterator<typ> ml::const_matrix_iterator<typ>::operator+(const int val) const {
    const_matrix_iterator<typ> ret = *this;
    ret += val;
    return ret;
}

template <class typ>
ml::const_matrix_iterator<typ>& ml::const_matrix_iterator<typ>::operator-=(const const_matrix_iterator<typ>& other){
    this -> curr -= other.curr;
    return *this;
}

template <class typ>
ml::const_matrix_iterator<typ>& ml::const_matrix_iterator<typ>::operator+=(const const_matrix_iterator<typ>& other){
    this -> curr += other.curr;
    return *this;
}

template <class typ>
ml::const_matrix_iterator<typ>& ml::const_matrix_iterator<typ>::operator-=(const int val){
    this -> curr -= val;
    return *this;  
}

template <class typ>
ml::const_matrix_iterator<typ>& ml::const_matrix_iterator<typ>::operator+=(const int val){
    this -> curr += val;
    return *this;
}

template <class typ>
const typ& ml::const_matrix_iterator<typ>::operator[](size_t i) const {
    return this -> curr[i];
}

template <class typ>
ml::const_matrix_iterator<typ>::~const_matrix_iterator() {}