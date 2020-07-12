//
// Created by Vova on 23.05.2020.
//

#pragma once

#include <chrono>
#include <string>

using namespace std::chrono_literals;
using namespace std::chrono;

class Timer {
private:
	std::string message;
	time_point<std::chrono::high_resolution_clock> start, end;
	duration<double> dur;
	bool printing;
public:
	explicit Timer(std::string process_name); //  = "Doing something unknown"
	Timer();
	~Timer();

	double get_time(const std::string& s = "ms");
	bool set_message(const std::string& s);
};





