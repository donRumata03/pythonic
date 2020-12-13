//
// Created by Vova on 13.12.2020.
//

#include "pythonic_pch.h"
#include "multirun_timer.h"

MultirunTimer::MultirunTimer() = default;

void MultirunTimer::clear()
{
	if (is_running) throw std::runtime_error("Can't clear, the Timer is running");

	m_total_time = nanoseconds{};
	m_runs = 0;
	is_running = false;

	m_time_history.clear();
}

void MultirunTimer::signal_work_starting()
{
	if (is_running) throw std::runtime_error("Timer is already running");

	is_running = true;
	m_last_time = Clock::now();
}

void MultirunTimer::signal_work_ending() {
	if (!is_running) throw std::runtime_error("Timer is not running");

	is_running = false;

	nanoseconds this_delay = Clock::now() - m_last_time;

	m_time_history.push_back(this_delay);
	m_total_time += this_delay;
	m_runs++;
}

MultirunTimer::nanoseconds MultirunTimer::total_time()
{
	if (is_running) throw std::runtime_error("Timer is running");

	return m_total_time;
}

size_t MultirunTimer::runs() const {
	if (is_running) throw std::runtime_error("Timer is running");

	return m_runs;
}

std::vector<MultirunTimer::nanoseconds> MultirunTimer::time_history()
{
	if (is_running) throw std::runtime_error("Timer is running");

	return m_time_history;
}
