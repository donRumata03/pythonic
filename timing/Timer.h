//
// Created by Vova on 23.05.2020.
//

#pragma once

#include "pythonic_pch.h"

// using namespace std::chrono_literals;
// using namespace std::chrono;

class Timer {
private:
	std::string message;
	chrono::time_point<std::chrono::high_resolution_clock> start, end;
	chrono::duration<double> dur;
	bool printing = true;
public:
	explicit Timer(std::string process_name); //  = "Doing something unknown"
	Timer();
	~Timer();


	enum class time_units {
		seconds,
		milliseconds,
		microseconds
	};
	double get_time(time_units unit = time_units::milliseconds);

	bool set_message(const std::string& s);
	bool remove_message();
};





