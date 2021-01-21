//
// Created by Vova on 31.08.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "Timer.h"

/**
 * Returns time in milliseconds!
 */
inline double measure_function_execution_time(
		const std::function<void(void)>& function_to_measure,
		const size_t times_of_execution = 1,
		const std::string& function_name = "",
		std::vector<double>* measurement_store = nullptr
		)
{
	if (!function_name.empty()) std::cout << "Launching function \"" << function_name << "\" " << times_of_execution << " times:" << std::endl;
	if (measurement_store) measurement_store->resize(times_of_execution);

	double total_time_elapsed = -1;

	{
		double last_time_point = 0;
		Timer t;

		for (size_t launch_number = 0; launch_number < times_of_execution; launch_number++) {
			function_to_measure();

			if (!function_name.empty()) {
				double time_now = t.get_time(Timer::time_units::milliseconds);
				double this_iteration_time = (time_now - last_time_point);
				double average_time = (time_now / (launch_number + 1.));

				std::cout << "\t" << launch_number + 1 << "\t/\t" << times_of_execution << "\t"
					<< "Total time: " << time_now << "\t"
				    << "Average: " << average_time << "\t"
				    << "This iteration: " << this_iteration_time
				<< std::endl;

				if (measurement_store) measurement_store->operator[](launch_number) = this_iteration_time;

				last_time_point = time_now;
			}
		}
		total_time_elapsed = t.get_time();
	}

	return total_time_elapsed / times_of_execution;
}

