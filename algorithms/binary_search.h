//
// Created by Vova on 20.01.2021.
//

/**
 * This module implements functionality for various sceneries of binary search application including:
 *
 * 1) Looking for an element in array
 * 2) 	BS for floating point functions: stops the search
 * 		if either the iteration limit has expired
 * 		or a good enough solution
 * 		(range endings are in ε-neighborhood of each other) has been found
 * 3) Discrete BS, but without any arrays. It just evaluates the target function and finds the boundary
 */

#pragma once

#include <pythonic_pch.h>
#include "maths/simple_functions.h"

/**
 * The most basic binary search function:
 *
 * @returns «left» and «right» indexes. The border. The Predicate is true for «right» and false for «left»
 */

template<class IndexValueType, class FunctorType>
std::pair<IndexValueType, IndexValueType> binary_search(const FunctorType& functor, IndexValueType l, IndexValueType r, IndexValueType exiting_difference) {
	static_assert(std::is_same_v<bool, decltype(functor(IndexValueType{}))>);

	while(r - l > exiting_difference) {
		IndexValueType mid = (r + l) / 2;

		if(functor(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}

	return { l, r };
}


template<class T>
std::optional<li> bs_find_element(const std::vector<T>& sorted_array, const T& element, bool increasing_order = true) {
	auto[l, r] = binary_search([&sorted_array, &element, increasing_order](li index){
		return (increasing_order) ? (sorted_array[index] >= element) : (sorted_array[index] <= element);
	}, -1ll, li(sorted_array.size()), 1ll);

	if ((r >= 0) and r < li(sorted_array.size()) and sorted_array[r] == element) {
		return r;
	}
	return {};
}


template<class T>
bool bs_has_element(const std::vector<T>& sorted_array, const T& element, bool increasing_order = true) {
//	auto[l, r] = binary_search([&sorted_array, &element, increasing_order](li index){
//		return (increasing_order) ? (sorted_array[index] >= element) : (sorted_array[index] <= element);
//	}, -1ll, li(sorted_array.size()), 1ll);
//
//	if ((r >= 0) and r < li(sorted_array.size()) and sorted_array[r] == element) {
//		return true;
//	}
//	return false;
	return bool(bs_find_element(sorted_array, element, increasing_order));
}


inline li bs_find_root_int_part(li number) {
	assert(number >= 0);

	auto[l, r] = binary_search([&number](li value){ return value * value > number; }, 0ll, number + 1, 1ll);

	return l;
}

inline double bs_find_float_root(double number, double eps) {
	assert(number >= 0);

	auto [l, r] = binary_search([&number](double root_candidate){ return square(root_candidate) > number; }, 0., number * 2, eps);
	
	return l;
}
