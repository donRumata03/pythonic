//
// Created by Vova on 26.05.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "other/typedefs.h"
#include "n_dim/nd_array.h"
#include "n_dim/nd_point.h"

pms count_number_density(
		const std::vector<double>& numbers,
		double percent_sigma = 0.1,
		lint target_number = -1,
		double percent_frame_width = 1
);

/*
nd_array<double> count_nd_density(
		const std::vector<nd_point<double>>& numbers,
		double percent_sigma = 0.1,
		lint target_number = -1,
		double percent_frame_width = 1
);
*/