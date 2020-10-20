//
// Created by Vova on 25.05.2020.
//

#pragma once

#include "pythonic_pch.h"

namespace hvn3 {

	enum class BytePrefix {
		// One kilobyte is equal to 1000 bytes.
		Decimal,
		// One kilobyte is equal to 1024 bytes.
		Binary
	};

	enum class ByteUnit {
		Metric,
		IEC,
		JEDEC
	};

	double RoundBytesToNearestBit(double bytes);

}
