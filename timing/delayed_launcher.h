#pragma once

/*
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
*/

#include "pythonic_pch.h"

template <class callable, class... arguments>
class delayed_launcher
{
	using function_type = std::function<typename std::invoke_result<callable, arguments...>::type()>;

	bool _is_enabled = true;
	function_type task;

public:
	delayed_launcher(double duration_seconds, bool async, callable&& f, arguments... args)
	{
		auto nanoseconds = static_cast<long long>(duration_seconds * double(1.e9));
		std::chrono::nanoseconds delay(nanoseconds);

		/*std::function<typename std::result_of<callable(arguments...)>::type()> */ task = std::bind(std::forward<callable>(f), std::forward<arguments>(args)...);

		if (async)
		{
			auto parent_ptr = this;

			std::thread([delay, parent_ptr]() {
				std::this_thread::sleep_for(delay);
				parent_ptr->task();
			}).detach();
		}
		else
		{
			std::this_thread::sleep_for(delay);
			task();
		}
	}

	void stop_launching() {
		_is_enabled = false;
	}
	void continue_launching() {
		_is_enabled = true;
	}
};
