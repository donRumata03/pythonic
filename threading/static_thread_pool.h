//
// Created by Vova on 17.10.2020.
//

#pragma once

#include "pythonic_pch.h"

class static_thread_pool
{
	std::vector<std::thread> m_threads;

public:
	explicit static_thread_pool(size_t thread_number, const std::function<void(size_t)>& function_to_launch_at_each_iteration);

	////////////////////////////////////////////////////////////////////////
	static_thread_pool(const static_thread_pool& other) = delete;
	static_thread_pool(static_thread_pool&& other) = delete;

	static_thread_pool& operator= (const static_thread_pool& other) = delete;
	static_thread_pool& operator= (static_thread_pool&& other) = delete;
	////////////////////////////////////////////////////////////////////////

	void join();
	void launch_tasks();


};


