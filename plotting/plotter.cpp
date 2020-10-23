//
// Created by Vova on 26.05.2020.
//

#include "plotter.h"

#include "maths/randomizator.h"

#include "files/file_walker.h"
#include "files/file_reader.h"
#include "maths/numpyic.h"
#include "displaying/type_printer.h"

// constexpr const char* data_filename = R"(D:\pythonic\plotting\plot_data.json)";

const fs::path plot_data_path = fs::path{pythonic_base_dir} / "plotting" / "plot_data.json";

void add_pairs_to_plot(const pms &points, const plot_params &params)
{
	json result = {};

	if (fs::exists(plot_data_path)) {
		try {
			result = json::parse(*read_file(plot_data_path));
		} catch (json::exception & e) {
			std::cerr << "Can`t parse json file with plots => ignoring its contents!" << std::endl;
		}
	}

	json this_json = {};
	if (!params.name.empty()) this_json["name"] = params.name;
	this_json["type"] = params.type;
	this_json["color"] = params.color;
	this_json["sorting"] = params.sorting;


	auto& data = this_json["data"];

	// data = std::vector<std::pair<double, double>>{};
	data = points;


	if (result.contains("plots"))
		result["plots"].push_back(this_json);
	else result["plots"] = json::array({ this_json });

	write_file(result.dump(4), plot_data_path);
}



void clear_plot()
{
	fs::remove(plot_data_path);
}

void show_plot(const plot_common_params& common_params)
{
	// assert(fs::exists({ std::string (data_filename) }));

	const std::string& output_filename = common_params.output_filename;
	const std::string& window_title = common_params.window_title;
	bool log_x = common_params.log_x;
	bool log_y = common_params.log_y;

	// if (!output_filename.empty() || log_x || log_y)
	// {
		// Inform Python to output plot to file by adding the filename to json
		auto file_read_attempt = read_file(plot_data_path);
		json j;
		if (file_read_attempt)
			j = json::parse(*file_read_attempt);
		else {
			j = json::object(); // json(std::unordered_map<std::string, double>());
			j["plots"] = json::array();
		}

		j["log_x"] = log_x;
		j["log_y"] = log_y;
		if (!output_filename.empty()) j["output_filename"] = output_filename;
		if (!window_title.empty()) j["window_title"] = window_title;

		write_file(j.dump(4), plot_data_path);
	// }

	system(go_to_python_dir_command);
	system(python_plot_command);
	clear_plot();
}

void add_line_to_plot(const line &l, const plot_params &params, const plot_range_params &range_params)
{
	add_function_to_plot(l, params, range_params);
}

void add_function_to_plot(const std::function<double(double)> &function, const plot_params &params, const plot_range_params &range_params, bool catch_and_ignore_exceptions)
{
	pms current_segment_points;
	auto real_params = params;

	pms res;
	if (!catch_and_ignore_exceptions) {
		res.reserve(range_params.get_step_number());
	}
	if (catch_and_ignore_exceptions && real_params.color == "default") {
		real_params.set_random_color();
	}

	bool has_exception = false;
	bool has_exceptions = false;


	auto xs = linspace(range_params.get_x0(), range_params.get_x1(), range_params.get_step_number(), true);
	size_t point_index = 0;
	for(const auto x : xs)
	{
		if (catch_and_ignore_exceptions) {
			double function_res;
			bool function_completed = false;

			try {
				function_res = function(x);
				if (!std::isnan(function_res)) function_completed = true;
			} catch (std::exception& e) {
				if (!has_exception) {
					std::cerr << "Exception occurred while adding function \"" << type_name<decltype(function)>()
					          << "\" to plot: \"" << e.what() << "\" (x = " << x << ")" << std::endl;
					has_exception = true;
				}
				else if (!has_exceptions) {
					std::cerr << "More than one exception caught while plotting!";
					has_exceptions = true;
				}
			}
			if (function_completed && std::isnan(function_res)) std::cerr << "Function output is NaN for input " << x << " while plotting!" << std::endl;

			if (function_completed) {
				current_segment_points.emplace_back(x, function_res); // TODO!!!!!!!! have different graph parts not to link them using line!!!!!!!!!!!
			}
			if (!current_segment_points.empty() && (!function_completed || point_index == xs.size() - 1)) {
				add_pairs_to_plot(current_segment_points, real_params); // todo: color autotune if it`s default!
				real_params.name = "";
				current_segment_points.clear();
			}

		}
		else {
			res.emplace_back(x, function(x));
		}
		point_index++;
	}
	if (!catch_and_ignore_exceptions) {
		add_pairs_to_plot(res, params);
	}
}

void add_graphs_to_plot (const std::vector<pms> &graphs, const plot_params &params)
{
	// TODO! (Deal with unique label and unique color which are required!)
}

void add_points_to_plot (const std::vector<point> &points, const plot_params &params)
{
	pms pairs;
	pairs.reserve(points.size());

	for (auto& pnt : points)
		pairs.push_back(std::pair<double, double>(pnt));

	add_pairs_to_plot(pairs, params);
}


std::string plot_params::get_random_plotting_color ()
{
	std::vector<std::string> colors = {
			"red",
			"green",
			"blue",
			"orange",
			// "yellow", /// Bad color!
			// "pink",
			"magenta",
			"violet"
	};

	std::random_device device;
	std::mt19937 matrix(device());
	return random_choice(colors, matrix);
}

void plot_params::set_random_color ()
{
	color = get_random_plotting_color();
}
