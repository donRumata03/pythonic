//
// Created by Vova on 27.05.2020.
//

#pragma once

#include "pythonic_pch.h"


std::vector<std::pair<size_t, size_t>>       distribute_task_ranges(size_t task_number, size_t group_number);
std::vector<std::pair<size_t, size_t>> dummy_distribute_task_ranges(size_t task_number, size_t group_number);


