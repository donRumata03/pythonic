//
// Created by Vova on 12.07.2020.
//

#pragma once

#include <pythonic.h>

#include <functional>
#include <utility>

using namespace date;

inline void date_test() {
	constexpr auto x1 = 2015_y/March/Sunday[last];
	std::cout << x1 << std::endl;

	auto today = system_clock::now();
	std::cout << today << '\n';
	std::invoke([](){});
	std::exception_ptr ex = std::make_exception_ptr(std::bad_alloc());
	// std::future_category();
}
