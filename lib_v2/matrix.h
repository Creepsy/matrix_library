#pragma once
#include <extended/vector>
#include <memory>
#include <new>
#include <iostream>
#include <string.h>


namespace extended{

	template<typename T>
	class matrix{
	private:
		//data container and data management
		extended::vector<T> data;
		size_t rowSize;
		inline const T& operator[](const size_t &index) const { return data[index]; }
 
	public:

		matrix();
		matrix(const size_t &rowCount, const size_t &rowSize) : data(rowCount*rowSize), rowSize(rowSize){}//constructor only allocates memory to initialize use assign or push
		matrix(const size_t &size) : data(size){}
		~matrix();//do nothing data already deallocates memory
		matrix(      matrix<T> &&other) : data(std::move(other.data)), rowSize(std::move(other.rowSize)){}
		matrix(const matrix<T>  &other) : data(other.data), rowSize(other.rowSize);

		T& operator()(const size_t &row, const size_t &index){ return data[(row*rowSize)+index]; }
		const T& operator()(const size_t &row, const size_t &index) const { return data[(row*rowSize)+index]; }

		matrix<T>& operator+(const matrix<T> &other) const;//TODO src code for this block
		matrix<T>& operator-(const matrix<T> &other) const;
		matrix<T>& operator*(const matrix<T> &other) const;
		matrix<T>& operator*(const T        &scalar) const;//scalar multiplication
		matrix<T>& operator/(const matrix<T> &other) const;
		//matrix<T>& operator%(const matrix<T> &other) const; not sure if usefull or what it shoulkd do

		void operator-=(const matrix<T>  &other){ *this = (*this) - other; }
		void operator+=(const matrix<T>  &other){ *this = (*this) + other; }
		void operator*=(const matrix<T>  &other){ *this = (*this) * other; }
		void operator*=(const T          &other){ *this = (*this) * other; }
		//void operator/=(const matrix<T>  &other){ *this = (*this) / other; } //not sure if usefull or what it should do

		void operator= (const matrix<T>  &other){ data = other.data;
												  rowSize = other.rowSize; }
		void operator= (	  matrix<T> &&other){ data = std::move(other.data);
												  rowSize = std::move(other.rowSize); }

		const size_t& row_size () const { return rowSize; }
		const size_t& row_count() const { return data.max_size()/row_size; }

		template<typename to>
		matrix<to>& cast();//TODO src code for this block
		void resize(const size_t rowCount, const size_t rowSize);
			  T* dataPtr()       {return data.get_ValPtr(); }
		const T* dataPtr() const {return data.get_ValPtr(); }
		inline const size_t size()     const { return data.size()    ; }
		inline const size_t max_size() const { return data.max_size(); }
		template<typename... args>
		inline void fill(args &...arguments){ data.assign<args>(max_size(), const args &...arguments); }//if it isnt trivially_default_constructible it wont do anythingn this function has to be called before using the matrix

		//iterator functions
		inline extended::vector<T>::normal_iterator begin (){ return data.begin (); }
		inline extended::vector<T>::normal_iterator end   (){ return data.end   (); }
		inline extended::vector<T>::normal_iterator rbegin(){ return data.rbegin(); }
		inline extended::vector<T>::normal_iterator rend  (){ return data.rend  (); }

		inline extended::vector<T>::const_iterator begin () const { return data.begin (); }
		inline extended::vector<T>::const_iterator end   () const { return data.end   (); }
		inline extended::vector<T>::const_iterator rbegin() const { return data.rbegin(); }
		inline extended::vector<T>::const_iterator rend  () const { return data.rend  (); }

	};

}