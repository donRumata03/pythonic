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

	// bool is_dead = false;
public:
	std::vector<size_t> dim_vals;
	size_t dims = 0;


	nd_array(size_t _dims, const std::vector<size_t>& _dim_vals, const T& filler = T{});
	explicit nd_array(const std::vector<size_t>& _dim_vals);



	/// Memory management:
	nd_array& operator= (const std::initializer_list<T>& list);

	nd_array& operator= (const nd_array& other);
	nd_array& operator= (nd_array&& other);

	~nd_array();


	class slice_type {

	private:
		nd_array<T>& m_array;
		std::vector<std::pair<size_t, size_t>> m_shifts;

	public:

		slice_type(nd_array<T>& arr, const std::vector<std::pair<size_t, size_t>> & shifts) : m_array(arr), m_shifts(shifts) {}

		T& operator[] (const std::vector<size_t>& indexes) const;

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

	slice_type slice(const std::vector<std::pair<size_t, size_t>> & indexes);

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



	/// Traverse:
	template <class Pred> void transform(const Pred& function);
	template <class Pred> void for_each(const Pred& function);
	template <class Pred> void indexed_for_each(const Pred& function);

	/// Utility:
	T sum();
	void fill(const T& elem);
	std::vector<nd_point<T>> get_points();

	/// Operators:
	template <class Tt> friend std::ostream& operator << (std::ostream&, const nd_array<Tt>& array);
	T& operator[] (const std::vector<size_t>& indexes) const;
	nd_array<T>& operator[] (size_t index) const;


private:
	/**
	 * \message:
	 * There are some useless for user functions below:
	 */
	template <class Pred> void indexed_for_each_impl(const Pred& function, std::vector<size_t>& indexes);




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



#include "nd_array.inl.h"

