//
// Created by Vova on 26.05.2020.
//

#pragma once

#include <pythonic.h>

inline void nd_point_test(){
	nd_point<double> pnt (10);

	std::cout << pnt.get_dimension_data() << std::endl;
	pnt = pnt + pnt;

	std::vector<nd_point<double>> ds;
	ds.push_back(pnt);


	std::cout << ds << std::endl;
}


inline void nd_indexing_test() {
	nd_array<double> arr(2, {3, 4});
	std::cout << "Made!" << std::endl;


	arr[{1, 3}] = 239.566;

	std::cout << arr[{2, 2}] << std::endl;
	std::cout << arr[{1, 3}] << std::endl;

	std::cout << arr << std::endl;

	arr.nd_array::~nd_array();
	std::cout << "destroyed" << std::endl;
}

inline void print_nd_array_test(){
	nd_array<double> arr({4, 4, 3});

	std::cout << arr.dim_vals.back() << std::endl;

	auto& arr1 = arr[1];

	for (size_t i = 0; i < arr.dim_vals.front(); i++) {
		for (size_t j = 0; j < arr.dim_vals[1]; j++) {
			for (size_t k = 0; k < arr.dim_vals.back(); k++) {
				arr[{ i, j, k }] = double(i + j + k) * pythonic_random();
			}
		}
	}

	std::cout << arr << std::endl;

	std::cout << std::endl << std::endl << std::endl;

	arr1.fill(100);

	std::cout << arr << std::endl;

}


inline void nd_get_points_test(){
	nd_array<double> arr(3, {2, 3, 2});

	std::cout << arr.get_points() << std::endl;
}

inline void nd_slicing_test(){
	nd_array<double> arr({3, 3, 2});
	nd_array<double>::slice_type slice = arr.slice({ { 0, 2 }, {0, 1} , {1, 2}});

	slice[{0, 0, 0}] = 100;
	slice[{0, 0, 1}] = 200;

	// slice[{1, 1}] = 1;

	std::cout << arr << std::endl;
}

inline void nd_for_eaches_test(){
	nd_array<double> arr({3, 3, 3});

	arr.transform([](double d) -> double { return d + pythonic_random() * 18.; });

	arr.for_each([](double d){ std::cout << d << std::endl; });


	std::cout << arr << std::endl;

	arr.indexed_for_each([](const std::pair<std::vector<size_t>, double>& d) { std::cout << d << std::endl; });
}

inline void test_nd_array_sum(){
	nd_array<double> arr({3, 3, 4});

	arr.fill(1);

	std::cout << arr.sum() << std::endl;

}



