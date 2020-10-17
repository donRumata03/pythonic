/**
 * Copyright (c) 2019, Marin Peko
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once


#include <atomic>
#include <chrono>
#include <future>
#include <functional>

class task_scheduler {
public:
	using Timestamp = std::chrono::time_point<
			std::chrono::system_clock,
			std::chrono::microseconds
	>;

	using Delay = std::chrono::milliseconds;
	using Period = std::chrono::milliseconds;

public:
	task_scheduler() : is_running_(true) {}
	task_scheduler(task_scheduler const& other) = delete;
	task_scheduler(task_scheduler&& other) = delete;

	task_scheduler& operator=(task_scheduler const& other) = delete;
	task_scheduler& operator=(task_scheduler&& other) = delete;

	~task_scheduler() = default;

	/**
	 * Schedules the specified task for execution at the specified time.
	 *
	 * @param time Time at which task is to be executed
	 * @param task Task to be scheduled
	 * @param args Arguments to be passed to the specified task
	 *
	 * @return Result of the task
	 */
	template <typename TimerTask, typename ... Args>
	std::future<void> schedule(Timestamp const& time, TimerTask task, Args... args) const {
		return std::async(std::launch::async, [=]() {
			auto start = std::chrono::time_point_cast<Timestamp::duration>(std::chrono::system_clock::now());
			auto delay = std::chrono::duration_cast<Delay>(time - start);
			std::this_thread::sleep_for(delay);
			std::invoke(task, args...);
		});
	}

	/**
	 * Schedules the specified task for repeated fixed-delay execution,
	 * beginning at the specified time.
	 *
	 * @param time   First time at which task is to be executed
	 * @param period Time between successive task executions
	 * @param task   Task to be scheduled
	 * @param args   Arguments to be passed to the specified task
	 *
	 * @return Result of the task
	 */
	template <typename TimerTask, typename ... Args>
	std::future<void> schedule(Timestamp const& time, Period const& period, TimerTask task, Args... args) const {
		return std::async(std::launch::async, [this, time, period, task, ...args = args]() {
			auto start = std::chrono::time_point_cast<Timestamp::duration>(std::chrono::system_clock::now());
			auto delay = std::chrono::duration_cast<Delay>(time - start);
			std::this_thread::sleep_for(delay);
			while (is_running_) {
				std::invoke(task, args...);
				std::this_thread::sleep_for(period);
			}
		});
	}

	/**
	 * Schedules the specified task for execution after the specified delay.
	 *
	 * @param delay Delay before task is to be executed
	 * @param task  Task to be scheduled
	 * @param args  Arguments to be passed to the specified task
	 *
	 * @return Result of the task
	 */
	template <typename TimerTask, typename ... Args>
	std::future<void> schedule(Delay const& delay, TimerTask task, Args... args) const {
		return std::async(std::launch::async, [=]() {
			std::this_thread::sleep_for(delay);
			std::invoke(task, args...);
		});
	}

	/**
	 * Schedules the specified task for repeated fixed-delay execution,
	 * beginning after the specified delay.
	 *
	 * @param delay  Delay before task is to be executed
	 * @param period Time between successive task executions
	 * @param task   Task to be scheduled
	 * @param args   Arguments to be passed to the specified task
	 *
	 * @return Result of the task
	 */
	template <typename TimerTask, typename ... Args>
	std::future<void> schedule(Delay const& delay, Period const& period, TimerTask task, Args... args) const {
		return std::async(std::launch::async, [=, this]() {
			std::this_thread::sleep_for(delay);
			while (is_running_) {
				std::invoke(task, args...);
				std::this_thread::sleep_for(period);
			}
		});
	}

	/**
	 * Terminates this timer, discarding any currently scheduled tasks.
	 */
	void cancel() noexcept {
		is_running_ = false;
	}

private:
	std::atomic<bool> is_running_;
};

