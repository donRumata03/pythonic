//
// Created by Vova on 26.05.2020.
//

#pragma once

#include <ostream>
#include "pch.h"

#include "nd_point.h"
#include "displaying/print_stl.h"

template<class T> class nd_array
{
private:
	nd_array<T>* arrays {nullptr};
	size_t this_dim_val;
	T* data {nullptr}; // Available only for 1-dim arrays

	bool is_dead = true;
public:
	std::vector<size_t> dim_vals;
	size_t dims = 0;


	nd_array(size_t _dims, const std::vector<size_t>& _dim_vals, const T& filler = T{});
	explicit nd_array(const std::vector<size_t>& _dim_vals);

	void fill(const T& elem)
	{
		for (size_t index = 0; index < this_dim_val; ++index) {
			if (dims == 1)
				data[index] = elem;
			else arrays[index].fill(elem);
		}
	}

	nd_array& operator= (const std::initializer_list<T>& list) { // TODO!
		return nd_array(0, std::vector());
	}

	T& operator[] (const std::vector<size_t>& indexes) const
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

	nd_array<T>& operator[] (size_t index) const {
		return arrays[index];
	}

	~nd_array()
	{
		// std::cout << "Calling ~: " << dims << std::endl;

		if (is_dead) {
			std::cout << "Stop... But I`m dead!!!" << std::endl;
			return;
		}

		if (dims > 1) {
			for (size_t arr_index = 0; arr_index < this_dim_val; arr_index++) arrays[arr_index].~nd_array();
		}

		operator delete[](arrays);
		delete[] data;

		is_dead = true;
	}


	class slice_type {

	private:
		nd_array<T>& m_array;
		std::vector<std::pair<size_t, size_t>> m_shifts;

	public:

		slice_type(nd_array<T>& arr, const std::vector<std::pair<size_t, size_t>> & shifts) : m_array(arr), m_shifts(shifts) {}

		T& operator[] (const std::vector<size_t>& indexes) const
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

		const nd_array<T>& get_full_array(){
			return m_array;
		}

		nd_array<T> get_sliced_array(){
			std::vector<size_t> slice_size;

			for (auto& sh : m_shift) {
				slice_size.emplace_back(sh.second - sh.first);
			}

			nd_array<T> res(slice_size);


		}

	};

	slice_type slice(const std::vector<std::pair<size_t, size_t>> & indexes)
	{
		assert(indexes.size() == this_dim_val);

		for (size_t dim_index = 0; dim_index < indexes.size(); ++dim_index) {
			assert(indexes[dim_index].first < indexes[dim_index].second);
		}

		return { *this, indexes };
	}

	explicit nd_array(const slice_type& slice)
	{
		// Copy elements!
		// TODO
	}
	explicit nd_array(slice_type&& slice)
	{
		// Copy elements!
		// TODO
	}
	nd_array& operator= (const nd_array& slice)
	{
		// Copy elements!
		if (this == &slice){
			return;
		}

		// TODO
	}
	nd_array& operator= (nd_array&& slice)
	{
		// Move elements!
		if (this == &slice){
			return;
		}
		// TODO
	}


	std::vector<nd_point<T>> get_points()
	{
		// TODO

		std::vector<nd_point<T>>  result;
		size_t all_number = 1;
		for (auto& i : dim_vals) all_number *= i;
		for (int i = 0; i < all_number; i++) { result.emplace_back(dims); }
		// recursive_get_points(result);
		return result;
	}




	template <class Pred> void transform(const Pred& function) {
		for (size_t index = 0; index < this_dim_val; ++index) {
			if (dims == 1)
				data[index] = function(data[index]);
			else arrays[index].transform(function);
		}
	}
	template <class Pred> void for_each(const Pred& function) {
		for (size_t index = 0; index < this_dim_val; ++index) {
			if (dims == 1)
				function(data[index]);
			else arrays[index].for_each(function);
		}
	}

	template <class Pred> void indexed_for_each(const Pred& function)
	{
		std::vector<size_t> index_storage = {};
		indexed_for_each_impl(function, index_storage);
	}


	T sum(){
		T res = T(0);

		for_each([&](const T& elem){ res += elem; });
		return res;
	}


	template <class Tt> friend std::ostream& operator << (std::ostream&, const nd_array<Tt>& array);


private:
	template <class Pred> void indexed_for_each_impl(const Pred& function, std::vector<size_t>& indexes) {
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


	/**
	 * \brief
	 * There are some useless for user functions below:
	 */

	/*
	void recursive_get_points(std::vector<nd_point<T>>& existing_points, vector<T> prefix)
	{
		size_t index = 0;

		if (dims != 1) {
			for(;index < this_dim_val; index++)
			for (size_t child_num = 0; child_num < this_dim_val; child_num++) arrays[child_num].recursive_get_points(existing_points);
		}
		else {
			for (; index < this_dim_val; index++) {
				existing_points.emplace_back(data[index], vector<T>);
			}
		}
	}
	 */


};

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

	is_dead = false;
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

template < class T >
nd_array<T>::nd_array (const std::vector<size_t> &_dim_vals) : nd_array(_dim_vals.size(), _dim_vals)
{}


