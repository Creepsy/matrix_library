#include "matrix.h"

template <class typ>
ml::matrix<typ>::matrix() : w(0), h(0), s(0) {
    this -> m = nullptr;
}

template <class typ>
ml::matrix<typ>::matrix(const std::initializer_list<std::initializer_list<typ>> data) : h(data.size()) {
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

template <class typ>
ml::matrix<typ>::matrix(const size_t width, const size_t height) : w(width), h(height), s(width * height) {
    this -> m = (typ*) malloc(sizeof(typ) * width * height);
}

template <class typ>
ml::matrix<typ>::matrix(matrix<typ>&& other) : w(other.w), h(other.h), s(other.s) {
    this -> m = other.m;
    other.m = nullptr;
}

template <class typ>
ml::matrix<typ>::matrix(const matrix<typ>& other) : w(other.w), h(other.h), s(other.s) {
    this -> m = (typ*) malloc(sizeof(typ) * other.w * other.h);
    for(size_t e = 0; e < other.s; e++){
        this -> m[e] = other.m[e];
    }
}

template <class typ>
const typ& ml::matrix<typ>::at(const size_t x, const size_t y) const {
    if(x >= this -> w || y >= this -> h) throw std::runtime_error("Index out of bounds!");
    return this -> m[x + y * this -> w];
}

template <class typ>
typ& ml::matrix<typ>::at(const size_t x, const size_t y) {
    if(x >= this -> w || y >= this -> h) throw std::runtime_error("Index out of bounds!");
    return this -> m[x + y * this -> w];
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix<typ>::begin() {
    return std::move(matrix_iterator<typ>(this -> m));
}

template <class typ>
ml::matrix_iterator<typ> ml::matrix<typ>::end() {
    return std::move(matrix_iterator<typ>(this -> m + this -> s));
}

template <class typ>
ml::const_matrix_iterator<typ> ml::matrix<typ>::begin() const {
    return std::move(const_matrix_iterator<typ>(this -> m));
}

template <class typ>
ml::const_matrix_iterator<typ> ml::matrix<typ>::end() const {
    return std::move(const_matrix_iterator<typ>(this -> m + this -> s));
}

template <class typ>
typ* ml::matrix<typ>::data() {
    return this -> m;
}

template <class typ>
typ const * ml::matrix<typ>::data() const {
    return this -> m;
}

template <class typ>
const size_t& ml::matrix<typ>::width() const {
    return this -> w;
}

template <class typ>
const size_t& ml::matrix<typ>::height() const {
    return this -> h;
}

template <class typ>
const size_t& ml::matrix<typ>::size() const {
    return this -> s;
}

template <class typ>
void ml::matrix<typ>::fill(const typ& val) {
    for(size_t e = 0; e < this -> s; e++){
        this -> m[e] = val;
    }
}

template <class typ>
void ml::matrix<typ>::swap(matrix<typ>& other) {
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

template <class typ>
ml::matrix<typ> ml::matrix<typ>::t() {
    matrix<typ> turned = {this -> h, this -> w};
    for(size_t x = 0; x < this -> w; x++){
        for(size_t y = 0; y < this -> h; y++){
            turned.m[y + x * this -> h] = this -> m[x + y * this -> w];
        }
    }
    return turned;
}

template <class typ>
ml::matrix<typ>::~matrix() {
    if(this -> m) {
        free(this -> m);
        this -> m = nullptr;
    }
}

template <class typ>
typ& ml::matrix<typ>::operator()(const size_t x, const size_t y) {
    return this -> at(x, y);
}

template <class typ>
void ml::matrix<typ>::operator=(const matrix<typ>& other) {
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

template <class typ>
const typ& ml::matrix<typ>::operator()(const size_t x, const size_t y) const {
    return this -> at(x, y);
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator+=(const o& val) {
    for(typ& e : *this){
        e += val;
    }

    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator+=(const matrix<o>& other) {
    if(this -> width() != other.width() || this -> height() != other.height())
        throw std::runtime_error("Sizes don't match!");

    for(size_t x = 0; x < other.width(); x++){
        for(size_t y = 0; y < other.height(); y++){
            (*this)(x, y) += other(x, y);
        }
    }
    
    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator-=(const o& val) {
    for(typ& e : *this){
        e -= val;
    }

    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator-=(const matrix<o>& other) {
    if(this -> width() != other.width() || this -> height() != other.height())
        throw std::runtime_error("Sizes don't match!");

    for(size_t x = 0; x < other.width(); x++){
        for(size_t y = 0; y < other.height(); y++){
            (*this)(x, y) -= other(x, y);
        }
    }
    
    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator*=(const o& val) {
    for(typ& e : *this){
        e *= val;
    }

    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator*=(const matrix<o>& other) {
    if(this -> width() != other.width() || this -> height() != other.height())
        throw std::runtime_error("Sizes don't match!");

    for(size_t x = 0; x < other.width(); x++){
        for(size_t y = 0; y < other.height(); y++){
            (*this)(x, y) *= other(x, y);
        }
    }
    
    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator/=(const o& val) {
    for(typ& e : *this){
        e /= val;
    }

    return *this;
}

template <class typ>
template <class o>
ml::matrix<typ>& ml::matrix<typ>::operator/=(const matrix<o>& other) {
    if(this -> width() != other.width() || this -> height() != other.height())
        throw std::runtime_error("Sizes don't match!");

    for(size_t x = 0; x < other.width(); x++){
        for(size_t y = 0; y < other.height(); y++){
            (*this)(x, y) /= other(x, y);
        }
    }
    
    return *this;
}

template <class t>
std::ostream& ml::operator<<(std::ostream& stream, const ml::matrix<t>& ma) {
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
void ml::swap(ml::matrix<t>& ma0, ml::matrix<t>& ma1) {
    ma0.swap(ma1);
}  

template <class to, class from>
ml::matrix<to> ml::matrix_cast(ml::matrix<from>& toCast){
    ml::matrix<to> casted = {toCast.w, toCast.h};
    for(size_t e = 0; e < toCast.s; e++){
        casted.m[e] = (to) toCast.m[e];
    }

    return std::move(casted);
}

template <class t, class o>
ml::matrix<t> ml::operator+(const ml::matrix<t>& ma, const o& val) {
    ml::matrix<t> ret = {ma};
    for(t& e : ret){
        e += val;
    }

    return std::move(ret);
}

template <class t>
ml::matrix<t> ml::operator+(const ml::matrix<t>& ma0, const ml::matrix<t>& ma1) {
    ml::matrix<t> ret = {ma0};

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
ml::matrix<t> ml::operator-(const ml::matrix<t>& ma, const o& val) {
    ml::matrix<t> ret = {ma};
    for(t& e : ret){
        e -= val;
    }

    return std::move(ret);
}

template <class t>
ml::matrix<t> ml::operator-(const ml::matrix<t>& ma0, const ml::matrix<t>& ma1) {
    ml::matrix<t> ret = {ma0};

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
ml::matrix<t> ml::operator*(const ml::matrix<t>& ma, const o& val) {
    ml::matrix<t> ret = {ma};
    for(t& e : ret){
        e *= val;
    }

    return std::move(ret);
}

template <class t>
ml::matrix<t> ml::operator*(const ml::matrix<t>& ma0, const ml::matrix<t>& ma1) {
    ml::matrix<t> ret = {ma0};

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
ml::matrix<t> ml::operator/(const ml::matrix<t>& ma, const o& val) {
    ml::matrix<t> ret = {ma};
    for(t& e : ret){
        e /= val;
    }

    return std::move(ret);
}

template <class t>
ml::matrix<t> ml::operator/(const ml::matrix<t>& ma0, const ml::matrix<t>& ma1) {
    ml::matrix<t> ret = {ma0};

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
ml::matrix<t> ml::operator%(const ml::matrix<t>& ma0, const ml::matrix<t>& ma1) {
    ml::matrix<t> ret = {ma1.width(), ma0.height()};

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