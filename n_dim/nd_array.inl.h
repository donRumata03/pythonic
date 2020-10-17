//
// Created by Vova on 24.07.2020.
//

#pragma once

// #include "nd_array.h"

///////////////////////////////////////////////
/// 	Nd array usual constructors:		///
///////////////////////////////////////////////
template < class T >
nd_array<T>::nd_array (const std::vector<size_t> &_dim_vals) : nd_array(_dim_vals.size(), _dim_vals)
{}

template < class T >
nd_array<T>::nd_array(size_t _dims, const std::vector<size_t> &_dim_vals, const T& filler) : dim_vals(_dim_vals), this_dim_val (_dim_vals.front()), dims(_dims) // Initialize dimension arrays
{
	assert(dims != 0);
	assert(dims == dim_vals.size() && "Dimension number doesn`t match with their sizes!");
	if (dims == 1) {
		data = new T[this_dim_val];
		for (size_t index = 0; index < this_dim_val; index++) data[index] = T(filler);
	}
	else {
		// arrays = shared_ptr<nd_array<T>>(new nd_array);
		// arrays =new nd_array(dims - 1, Slice(dim_vals, 1, dim_vals.size()));
		arrays = reinterpret_cast<nd_array<T>*>(operator new[] (this_dim_val * sizeof(nd_array<T>)));
		auto next_dim_vals = Slice(dim_vals, 1, dim_vals.size());
		for (size_t i = 0; i < this_dim_val; i++) {
			auto this_addr = arrays + i;
			auto ptr = new (this_addr) nd_array<T>(dims - 1, next_dim_vals);
		}
	}
}

///////////////////////////////////////////////
/// 		Nd array memory management:		///
///////////////////////////////////////////////

/// Main (The) Destructor:
template < class T >
nd_array<T>::~nd_array ()
{
	// std::cout << "Calling ~: " << dims << std::endl;

/*
		if (is_dead) {
			std::cout << "Stop... But I`m dead!!!" << std::endl;
			return;
		}
*/

	if (arrays && dims > 1) {
		for (size_t arr_index = 0; arr_index < this_dim_val; arr_index++) arrays[arr_index].~nd_array();
	}

	operator delete[](arrays);
	delete[] data;

	arrays = nullptr;
	data = nullptr;
}


template < class T >
nd_array<T> &nd_array<T>::operator= (const std::initializer_list<T> &list)
{
	// TODO!
	return *this;
}


template < class T >
nd_array<T> &nd_array<T>::operator= (const nd_array &other)
{
	// Deep copy elements!
	if (this != &other){

	}

	return *this;
}


template < class T >
nd_array<T> &nd_array<T>::operator= (nd_array &&slice)
{
	// Move elements!
	if (this != &slice){

	}
	return *this;
}

///////////////////////////////////////////////
/// 			Nd array operators:			///
///////////////////////////////////////////////


template < class T >
T &nd_array<T>::operator[] (const std::vector<size_t> &indexes) const
{
	assert(dims == indexes.size());

	if (indexes[0] >= this_dim_val)
		throw std::out_of_range(std::string("Index (") + std::to_string(indexes[0]) + ") is too big, because the size of this dimension of the array is " + std::to_string(this_dim_val));

	if (indexes[0] < 0)
		throw std::out_of_range(std::string("Index (") + std::to_string(indexes[0]) + ") is too small, because it`s below zero!!!");


	if (dims == 1) {
		return data[indexes[0]];
	}
	return arrays[indexes[0]][Slice(indexes, 1, dims)];
}



template<class T> std::ostream &operator<< (std::ostream &os, const nd_array<T> &array)
{
	if (array.dims == 1) {
		std::vector<T> to_print(array.data, array.data + array.dim_vals[0]);
		os << to_print; //  << std::endl;
	}
	else {
		os << "[";

		size_t new_lines = array.dims - 1;

		for(size_t arr_index = 0; arr_index < array.this_dim_val; arr_index++){
			// os << array.arrays[arr_index];
			os << array[arr_index];

			if (arr_index != array.this_dim_val - 1) {
				os << ",";
				for(size_t nl_i = 0; nl_i < new_lines; nl_i++){
					os << "\n";
				}
			}
		}
		os << "]";
	}
	return os;
}


///////////////////////////////////////////////
/// 	Nd array private impl functions:	///
///////////////////////////////////////////////
// template < class T, class Pred >
template<class T> template<class Pred>
void nd_array<T>::indexed_for_each_impl (const Pred &function, std::vector<size_t> &indexes)
{
	indexes.push_back(0);

	for (size_t index = 0; index < this_dim_val; ++index) {
		/*
		std::vector<size_t> this_new_indexes(indexes.size() + 1);
		for (size_t i = 0; i < indexes.size(); ++i) {

		}
		*/

		indexes.back() = index;

		if (dims == 1)
			function(std::pair{ indexes, data[index] });
		else arrays[index].indexed_for_each_impl(function, indexes);

	}
	indexes.pop_back();
}

template < class T >
nd_array<T> &nd_array<T>::operator[] (size_t index) const
{
	return arrays[index];
}

///////////////////////////////////////////////
/// 		Nd array traverse methods:		///
///////////////////////////////////////////////

template < class T >
template < class Pred >
void nd_array<T>::transform (const Pred &function)
{
	for (size_t index = 0; index < this_dim_val; ++index) {
		if (dims == 1)
			data[index] = function(data[index]);
		else arrays[index].transform(function);
	}
}

template < class T >
template < class Pred >
void nd_array<T>::for_each (const Pred &function)
{
	for (size_t index = 0; index < this_dim_val; ++index) {
		if (dims == 1)
			function(data[index]);
		else arrays[index].for_each(function);
	}
}


template < class T >
template < class Pred >
void nd_array<T>::indexed_for_each (const Pred &function)
{
	std::vector<size_t> index_storage = {};
	indexed_for_each_impl(function, index_storage);
}

///////////////////////////////////////////////
/// 	Nd array useful utility methods:	///
///////////////////////////////////////////////

template < class T >
T nd_array<T>::sum ()
{
	T res = T(0);

	for_each([&](const T& elem){ res += elem; });
	return res;
}

template < class T >
void nd_array<T>::fill (const T &elem)
{
	for (size_t index = 0; index < this_dim_val; ++index) {
		if (dims == 1)
			data[index] = elem;
		else arrays[index].fill(elem);
	}
}


template < class T >
std::vector<nd_point<T>> nd_array<T>::get_points ()
{
	// TODO

	std::vector<nd_point<T>>  result;
	size_t all_number = 1;
	for (auto& i : dim_vals) all_number *= i;
	for (int i = 0; i < all_number; i++) { result.emplace_back(dims); }
	// recursive_get_points(result);
	return result;
}



///////////////////////////////////////////////
/// 	Nd array slice type methods:		///
///////////////////////////////////////////////

// Making slices:
template < class T >
typename nd_array<T>::slice_type nd_array<T>::slice (const std::vector<std::pair<size_t, size_t>> &indexes)
{
	assert(indexes.size() == this_dim_val);

	for (size_t dim_index = 0; dim_index < indexes.size(); ++dim_index) {
		assert(indexes[dim_index].first < indexes[dim_index].second);
	}

	return { *this, indexes };
}



template < class T >
T &nd_array<T>::slice_type::operator[] (const std::vector<size_t> &indexes) const
{
	assert(indexes.size() == m_shifts.size());
	assert(m_shifts.size() == m_array.dims);

	auto modified_indexes = indexes;

	// Add firsts:
	for (size_t i = 0; i < modified_indexes.size(); ++i) {
		modified_indexes[i] += m_shifts[i].first;

		/// Check if they are in range!
		assert(modified_indexes[i] < m_shifts[i].second);
	}

	return m_array[modified_indexes];
}
