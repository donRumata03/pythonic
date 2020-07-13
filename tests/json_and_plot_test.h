//
// Created by Vova on 26.05.2020.
//

#pragma once

#include <json.hpp>

#include "plotting/plotter.h"
#include "maths/numpyic.h"

using nlohmann::json;

inline void simple_test_json() {
	json j = json::parse(R"({
					"No" : 129,
					"Hello!" : null
				})");

	std::cout << j["No"] << std::endl;
}


inline void basic_plot_test()
{
	add_to_plot({{0, 0}, {1, 0}, {10, 100}, {20, 150}}, {});
	try {
		show_plot({false, true, R"(D:\pythonic\plotting\test_plot.png)" });
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

inline void line_plot_test(){
	line l(10, -0);
	add_line_to_plot(l, {"some line by Лев Толстой", "red", "plot", false}, {-5, 5, 0.001});
	show_plot({false, true});
}

inline void throwing_function_plotting_test(){

	add_function_to_plot(
			[] (double x) -> double {
				if (x > -1 && x < 1) { throw std::range_error(""); }
				return sqrt(abs(x) - 1);
			},
			{ "test_name" }, { double(-2), double(2), size_t(100000) }, true);

	show_plot();
}

inline void throwing_everywhere_function_test()
{
	add_function_to_plot(
			[] (double x) -> double {
				throw std::range_error("");
				return sqrt(-x * x);
			},
			{ "test_name" }, { double(-2), double(2), size_t(100000) }, true);

	show_plot();
}
