//
// Created by Vova on 20.01.2021.
//

#pragma once

#include <algorithms/binary_search.h>

inline void bs_has_element_test()
{
	std::vector<li> test_array = {
			-3, 0, 10, 83, 228
	};
	std::cout << std::boolalpha;
	std::vector<li> test_elements = {
			-5, -3, -2, 0, 83, 84, 228, 3214234
	};

	for (auto& element : test_elements) {
		std::cout << element << " : " << bs_has_element(test_array, element) << std::endl;
	}
}

inline void bs_root_test() {
	std::vector<li> numbers = {
			0, 1, 2, 3, 4, 5, 7, 8, 9, 16, 141, 142, 144
	};

	for (auto& num : numbers) {
		std::cout << "sqrt(" << num << ") ≈ " << bs_find_root_int_part(num) << std::endl;
	}
}
