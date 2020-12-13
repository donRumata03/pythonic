//
// Created by Vova on 13.12.2020.
//

#pragma once


class MultirunTimer
{
public:
	using nanoseconds = std::chrono::nanoseconds;

	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;

	MultirunTimer();
	void clear();

	void signal_work_starting();
	void signal_work_ending();

	nanoseconds total_time();
	[[nodiscard]] size_t runs() const;
	nanoseconds average_time() { return total_time() / runs(); };

	std::vector<nanoseconds> time_history();

private:

	TimePoint m_last_time{};
	bool is_running = false;

	nanoseconds m_total_time{};
	size_t m_runs{};
	std::vector<nanoseconds> m_time_history{};
};



