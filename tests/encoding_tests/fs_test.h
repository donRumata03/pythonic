//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

inline void test_fs_current_path()
{
	std::cout << fs::current_path() << std::endl;
}


