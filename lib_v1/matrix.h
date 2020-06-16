#pragma once

#include <malloc.h>
#include <stdexcept>
#include <ostream>
#include <initializer_list>
#include <string>

#include "matrix_iter.h"

namespace ml
{
    template <class typ>
    class matrix {
    private:
        typ* m;
        size_t w, h, s;
    public:
        matrix() : w(0), h(0), s(0) {
            this -> m = nullptr;
        }

        matrix(const std::initializer_list<std::initializer_list<typ>> data) : h(data.size()) {
            this -> w = 0;
            for(const std::initializer_list<typ>& r : data){
                if(r.size() > this -> w) this -> w = r.size();
            }
            this -> s = this -> h * this -> w;
            this -> m = (typ*) malloc(sizeof(typ) * this -> s);

            for(size_t y = 0; y < this -> h; y++){
                const std::initializer_list<typ>& c = *(data.begin() + y);
                for(size_t x = 0; x < c.size(); x++){
                    this -> m[x + y * this -> w] = *(c.begin() + x);
                }
            }
        }

        matrix(const size_t width, const size_t height) : w(width), h(height), s(width * height) {
            this -> m = (typ*) malloc(sizeof(typ) * width * height);
        }

        matrix(matrix<typ>&& other) : w(other.w), h(other.h), s(other.s) {
            this -> m = other.m;
            other.m = nullptr;
        }

        matrix(const matrix<typ>& other) : w(other.w), h(other.h), s(other.s) {
            this -> m = (typ*) malloc(sizeof(typ) * other.w * other.h);
            for(size_t e = 0; e < other.s; e++){
                this -> m[e] = other.m[e];
            }
        }

        const typ& at(const size_t x, const size_t y) const {
            if(x >= this -> w || y >= this -> h) throw std::runtime_error("Index out of bounds!");
            return this -> m[x + y * this -> w];
        }

        typ& at(const size_t x, const size_t y) {
            if(x >= this -> w || y >= this -> h) throw std::runtime_error("Index out of bounds!");
            return this -> m[x + y * this -> w];
        }

        matrix_iterator<typ> begin() {
            return std::move(matrix_iterator<typ>(this -> m));
        }

        matrix_iterator<typ> end() {
            return std::move(matrix_iterator<typ>(this -> m + this -> s));
        }

        const_matrix_iterator<typ> begin() const {
            return std::move(const_matrix_iterator<typ>(this -> m));
        }

        const_matrix_iterator<typ> end() const {
            return std::move(const_matrix_iterator<typ>(this -> m + this -> s));
        }
        
        typ* data() {
            return this -> m;
        }

        typ const * data() const {
            return this -> m;
        }

        const size_t& width() const {
            return this -> w;
        }

        const size_t& height() const {
            return this -> h;
        }

        const size_t& size() const {
            return this -> s;
        }

        void fill(const typ& val){
            for(size_t e = 0; e < this -> s; e++){
                this -> m[e] = val;
            }
        }

        void swap(matrix<typ>& other){
            const size_t tW = other.w, tH = other.h, tS = other.s;
            typ* tM = other.m;

            other.w = this -> w;
            other.h = this -> h;
            other.s = this -> s;
            other.m = this -> m;

            this -> w = tW;
            this -> h = tH;
            this -> s = tS;
            this -> m = tM;
        }

        matrix<typ> t(){
            matrix<typ> turned = {this -> h, this -> w};
            for(size_t x = 0; x < this -> w; x++){
                for(size_t y = 0; y < this -> h; y++){
                    turned.m[y + x * this -> h] = this -> m[x + y * this -> w];
                }
            }
            return turned;
        }

        ~matrix() {
            if(this -> m) {
                free(this -> m);
                this -> m = nullptr;
            }
        }
        
        template <class t>
        friend std::ostream& operator<<(std::ostream& stream, const matrix<t>& ma);

        template <class t>
        friend void std::swap(matrix<t>& ma0, matrix<t>& ma1);

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

        typ& operator()(const size_t x, const size_t y) {
            return this -> at(x, y);
        }

        void operator=(const matrix<typ>& other) {
            if(this -> m) {
                free(this -> m);
                this -> m = nullptr;
            }

            this -> w = other.w;
            this -> h = other.h;
            this -> s = other.s;
            this -> m = other.m;

            this -> m = (typ*) malloc(sizeof(typ) * other.w * other.h);
            for(size_t e = 0; e < other.s; e++){
                this -> m[e] = other.m[e];
            }
        }

        const typ& operator()(const size_t x, const size_t y) const {
            return this -> at(x, y);
        }

        template <class o>
        matrix<typ>& operator+=(const o& val) {
            for(typ& e : *this){
                e += val;
            }

            return *this;
        }

        template <class o>
        matrix<typ>& operator+=(const matrix<o>& other) {
            if(this -> width() != other.width() || this -> height() != other.height())
                throw std::runtime_error("Sizes don't match!");

            for(size_t x = 0; x < other.width(); x++){
                for(size_t y = 0; y < other.height(); y++){
                    (*this)(x, y) += other(x, y);
                }
            }
            
            return *this;
        }

        template <class o>
        matrix<typ>& operator-=(const o& val) {
            for(typ& e : *this){
                e -= val;
            }

            return *this;
        }

        template <class o>
        matrix<typ>& operator-=(const matrix<o>& other) {
            if(this -> width() != other.width() || this -> height() != other.height())
                throw std::runtime_error("Sizes don't match!");

            for(size_t x = 0; x < other.width(); x++){
                for(size_t y = 0; y < other.height(); y++){
                    (*this)(x, y) -= other(x, y);
                }
            }
            
            return *this;
        }

        template <class o>
        matrix<typ>& operator*=(const o& val) {
            for(typ& e : *this){
                e *= val;
            }

            return *this;
        }

        template <class o>
        matrix<typ>& operator*=(const matrix<o>& other) {
            if(this -> width() != other.width() || this -> height() != other.height())
                throw std::runtime_error("Sizes don't match!");

            for(size_t x = 0; x < other.width(); x++){
                for(size_t y = 0; y < other.height(); y++){
                    (*this)(x, y) *= other(x, y);
                }
            }
            
            return *this;
        }

        template <class o>
        matrix<typ>& operator/=(const o& val) {
            for(typ& e : *this){
                e /= val;
            }

            return *this;
        }

        template <class o>
        matrix<typ>& operator/=(const matrix<o>& other) {
            if(this -> width() != other.width() || this -> height() != other.height())
                throw std::runtime_error("Sizes don't match!");

            for(size_t x = 0; x < other.width(); x++){
                for(size_t y = 0; y < other.height(); y++){
                    (*this)(x, y) /= other(x, y);
                }
            }
            
            return *this;
        }

    }; 

    template <class t>
    std::ostream& operator<<(std::ostream& stream, const matrix<t>& ma) {
        stream << '[' << std::endl;
        for(size_t y = 0; y < ma.h; y++){
            stream << "  [";
            for(size_t x = 0; x < ma.w; x++){
                stream << ma.at(x, y);
                if(x != ma.w - 1) stream << ", ";
            }
            stream << ']';
            if(y != ma.h - 1) stream << ',';
            stream << std::endl;
        }
        return stream << ']';
    }

    template <class t>
    void swap(matrix<t>& ma0, matrix<t>& ma1) {
        ma0.swap(ma1);
    }  

    template <class to, class from>
    matrix<to> matrix_cast(matrix<from>& toCast){
        matrix<to> casted = {toCast.w, toCast.h};
        for(size_t e = 0; e < toCast.s; e++){
            casted.m[e] = (to) toCast.m[e];
        }

        return std::move(casted);
    }

    template <class t, class o>
    matrix<t> operator+(const matrix<t>& ma, const o& val) {
        matrix<t> ret = {ma};
        for(t& e : ret){
            e += val;
        }

        return std::move(ret);
    }

    template <class t>
    matrix<t> operator+(const matrix<t>& ma0, const matrix<t>& ma1) {
        matrix<t> ret = {ma0};

        if(ma0.width() != ma1.width() || ma0.height() != ma1.height())
            throw std::runtime_error("Sizes don't match!");

        for(size_t x = 0; x < ret.width(); x++){
            for(size_t y = 0; y < ret.height(); y++){
                ret(x, y) = ma0(x, y) + ma1(x, y);
            }
        }
        
        return std::move(ret);
    }

    template <class t, class o>
    matrix<t> operator-(const matrix<t>& ma, const o& val) {
        matrix<t> ret = {ma};
        for(t& e : ret){
            e -= val;
        }

        return std::move(ret);
    }

    template <class t>
    matrix<t> operator-(const matrix<t>& ma0, const matrix<t>& ma1) {
        matrix<t> ret = {ma0};

        if(ma0.width() != ma1.width() || ma0.height() != ma1.height())
            throw std::runtime_error("Sizes don't match!");

        for(size_t x = 0; x < ret.width(); x++){
            for(size_t y = 0; y < ret.height(); y++){
                ret(x, y) = ma0(x, y) - ma1(x, y);
            }
        }
        
        return std::move(ret);
    }

    template <class t, class o>
    matrix<t> operator*(const matrix<t>& ma, const o& val) {
        matrix<t> ret = {ma};
        for(t& e : ret){
            e *= val;
        }

        return std::move(ret);
    }

    template <class t>
    matrix<t> operator*(const matrix<t>& ma0, const matrix<t>& ma1) {
        matrix<t> ret = {ma0};

        if(ma0.width() != ma1.width() || ma0.height() != ma1.height())
            throw std::runtime_error("Sizes don't match!");

        for(size_t x = 0; x < ret.width(); x++){
            for(size_t y = 0; y < ret.height(); y++){
                ret(x, y) = ma0(x, y) * ma1(x, y);
            }
        }
        
        return std::move(ret);
    }

    template <class t, class o>
    matrix<t> operator/(const matrix<t>& ma, const o& val) {
        matrix<t> ret = {ma};
        for(t& e : ret){
            e /= val;
        }

        return std::move(ret);
    }

    template <class t>
    matrix<t> operator/(const matrix<t>& ma0, const matrix<t>& ma1) {
        matrix<t> ret = {ma0};

        if(ma0.width() != ma1.width() || ma0.height() != ma1.height())
            throw std::runtime_error("Sizes don't match!");

        for(size_t x = 0; x < ret.width(); x++){
            for(size_t y = 0; y < ret.height(); y++){
                ret(x, y) = ma0(x, y) / ma1(x, y);
            }
        }
        
        return std::move(ret);
    }

    template <class t>
    matrix<t> operator%(const matrix<t>& ma0, const matrix<t>& ma1) {
        matrix<t> ret = {ma1.width(), ma0.height()};

        if(ma0.width() != ma1.height())
            throw std::runtime_error("Can't multiply a " + 
                std::to_string(ma0.width()) + "x" + std::to_string(ma0.height()) +
                " matrix with a " + 
                std::to_string(ma1.width()) + "x" + std::to_string(ma1.height()) + 
                " matrix!"
            );

        for(size_t row = 0; row < ma0.height(); row++){
            for(size_t col = 0; col < ma1.width(); col++){
                t sum = {};
                for(size_t r = 0; r < ma1.height(); r++){ 
                    sum += ma0(r, row) * ma1(col, r);
                }
                ret(col, row) = sum;
            }
        }

        return std::move(ret);
    }
}