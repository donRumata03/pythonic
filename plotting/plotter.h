//
// Created by Vova on 26.05.2020.
//

#pragma once

#include "pythonic_pch.h"

#include <other/typedefs.h>
#include "geometry/line.h"
#include "maths/numpyic.h"
#include "other/python_builtins.h"




constexpr const char* go_to_python_dir_command = "cd \"C:/Program Files (x86)/Python37-32/\"";
constexpr const char* python_plot_command = "python.exe D:/pythonic/plotting/plotter.py";



struct plot_params
{
	std::string name = "";
	std::string color = "default";
	std::string type = "plot";
	bool sorting = false;

	static std::string get_random_plotting_color();
	void set_random_color();
};

struct plot_common_params
{
	bool log_x = false;
	bool log_y = false;

	std::string output_filename = "";
	std::string window_title = "";
};

class plot_range_params
{
	double x0 = 0;
	double x1 = 50;

	size_t step_number = 50;
	double step_size = 1;


public:
	plot_range_params(double x0, double x1, double step) : x0(x0), x1(x1), step_size(step) {
		assert(x0 < x1);
		step_number = 1 + size_t(std::round((x1 - x0) / step));
	}

	plot_range_params(double x0, double x1, size_t steps) : x0(x0), x1(x1), step_number(steps) {
		assert(x0 < x1);
		assert(steps != 1 && "There must be at least 2 points: the start and the end!");

		step_size = (x1 - x0) / double(steps - 1);
	}

	[[nodiscard]] double get_x0() const
	{
		return x0;
	}

	[[nodiscard]] double get_x1() const
	{
		return x1;
	}

	[[nodiscard]] size_t get_step_number() const
	{
		return step_number;
	}

	[[nodiscard]] double get_step_size() const
	{
		return step_size;
	}

};


void add_pairs_to_plot(const pms& points, const plot_params& params = {});
inline void add_vectors_to_plot(const std::vector<double>& xs, const std::vector<double>& ys, const plot_params& params = {}) { 
	add_pairs_to_plot(zip(xs, ys), params); 
}
void add_points_to_plot(const std::vector<point>& points, const plot_params& params = {});
void add_graphs_to_plot(const std::vector<pms>& graphs, const plot_params& params = {});

void add_line_to_plot(const line& l, const plot_params& params, const plot_range_params& range_params);
void add_function_to_plot(const std::function<double(double)>& function, const plot_params &params, const plot_range_params& range_params, bool catch_and_ignore_exceptions = true);

void show_plot(const plot_common_params& common_params = {});
void clear_plot();


