//
// Created by Vova on 23.05.2020.
//

#include "Timer.h"
#include <iostream>

#include <utility>


using namespace std::chrono_literals;
using namespace std::chrono;


Timer::Timer(std::string process_name)
		: printing(true), message (std::move(process_name)), dur(0ms) {

	if (printing) {
		std::cout << message << "...\n";
	}
	start = high_resolution_clock::now();
}


Timer::Timer() : dur{} {
	printing = false;
	message = "";
	start = high_resolution_clock::now();
}

Timer::~Timer() {
	if(!printing) return;
	end = high_resolution_clock::now();
	dur = end - start;

	double s = dur.count();
	double ms = s * 1000.0;
	double mks = ms * 1000.0;

	std::cout << message << " took " << s << " s (" << ms << " ms; " << mks << "mks)" << std::endl;
}

double Timer::get_time(time_units unit) {
	end = high_resolution_clock::now();
	dur = end - start;

	// time_point<system_clock, duration> e;
	// e = high_resolution_clock::now();

	double sec = dur.count();
	// double ms = dur.count() * 1000.0;

	if (unit == time_units::milliseconds) return sec * 1000.;
	else if (unit == time_units::seconds) return sec;
	else if (unit == time_units::microseconds) return sec * 1000'000.;

	throw std::runtime_error("bad enum value");
}

bool Timer::set_message(const std::string& s)
{
	bool ret = printing;
	message = s;
	printing = true;
	return ret;
}

bool Timer::remove_message ()
{
	bool initial_state = printing;
	printing = false;
	message.clear();
	return initial_state;
}


