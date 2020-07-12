//
// Created by Vova on 26.05.2020.
//

#pragma once

#include "other/typedefs.h"

pms smooth(
		const pms& points,
		double percent_sigma = 0.1,
		lint resultive_number_of_points = -1,
		double percent_frame_width = 1
);    // resultive_number_of_points = -1 if it is automatic




