//
// Created by Vova on 24.05.2020.
//

#pragma once

#include "../other/typedefs.h"

template <class T>
inline T sgn(const T& val)
{
	if (val > 0) return static_cast<T>(1);
	if (val < 0) return static_cast<T>(-1);
	return static_cast<T>(0);
}

template <class T>
inline T square(const T& val)
{
	return val * val;
}

template <class T>
inline T cube(const T& val)
{
	return val * val * val;
}


inline constexpr double pi = 3.1415926535897932384626433832795028841971693993751058209749;
inline constexpr double e = 2.71828182845904523536028747135266249775724709369995957496696;
