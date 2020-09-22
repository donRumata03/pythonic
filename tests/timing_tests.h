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

	auto today = chrono::system_clock::now();
	std::cout << today << '\n';
	std::invoke([](){});
	std::exception_ptr ex = std::make_exception_ptr(std::bad_alloc());
	// std::future_category();

	auto v = std::vector<int>();
	std::map<int, std::string>::value_type t;

}



inline void test_delayed_launch() {
	// invoke_function([](int i, int j){ std::cout << i << " " << j << std::endl; }, 10, 100);
	// invoke_function<int, double>([](int i, double j){ std::cout << i << " " << j << std::endl; }, 1, 10.);

	// Synchronous:
	delayed_launcher sync_launcher(1., false, [](double value){ std::cout << value << std::endl; }, 38.5);
	std::cout << "Main code runs!" << std::endl;

	// Asynchronous:
	delayed_launcher async_launcher(3., true, [](double value){ std::cout << value << std::endl; }, 36.6);
	std::cout << "Main code runs!" << std::endl;
	while(true);

}

inline void test_task_scheduler(){
	task_scheduler timer;

	auto ts = std::chrono::time_point_cast<task_scheduler::Timestamp::duration>(std::chrono::system_clock::now());
	ts = ts + 3s;

	chrono::seconds seconds1 = 4s;
	auto minutes1 = chrono::round<chrono::minutes>(seconds1);

	chrono::time_point<std::chrono::high_resolution_clock> t = chrono::high_resolution_clock::now();
	chrono::time_point<std::chrono::high_resolution_clock> t2 = chrono::high_resolution_clock::now();

	std::cout << (t2 - t).count() << "ns" << std::endl;

	auto result = timer.schedule(
			ts, task_scheduler::Period{ 1000 },
			[] {
				std::cout << "Task body" << std::endl;
			}
	);

	std::invoke([](){});

	std::cout << "In main function" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds{ 8 });
	timer.cancel();
	std::cout << "Timer cancelled" << std::endl;

}

inline void easy_measure_test() {
	std::cout << measure_function_execution_time([](){
		circle c({1., 100}, {100., 10}, {12, 300});
	}, 100000 /*, "Helloing" */) << std::endl;

	std::cout << measure_function_execution_time([](){
		circle c({1., 100}, {100., 10});
	}, 100000 /*, "Helloing" */) << std::endl;


	std::cout << circle({1., 100}, {100., 10}, {12, 300}) << std::endl;
}
