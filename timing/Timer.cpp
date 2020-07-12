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

	double ms = dur.count() * 1000.0;
	double mks = ms * 1000.0;
	double s = dur.count();

	std::cout << message << " took " << s << " s (" << ms << " ms; " << mks << "mks)" << std::endl;
}

double Timer::get_time(const std::string& s) {
	end = high_resolution_clock::now();
	dur = end - start;

	// time_point<system_clock, duration> e;
	// e = high_resolution_clock::now();

	double ms = dur.count() * 1000.0;
	double sec = dur.count();

	if (s == "ms") return ms;
	else if (s == "s") return sec;

	return ms;
}

bool Timer::set_message(const std::string& s)
{
	bool ret = printing;
	message = s;
	printing = true;
	return ret;
}


