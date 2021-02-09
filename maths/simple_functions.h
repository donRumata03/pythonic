//
// Created by Vova on 24.05.2020.
//

#pragma once

#include "../other/typedefs.h"
#include <ciso646>

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

template <class Float, std::enable_if_t<std::is_floating_point_v<Float>, void*> nothing = nullptr>
bool almost_equal(Float float1, Float float2, Float relative_eps = 1e-10, Float absolute_eps = 1e-15) {
	if (float1 == float2) return true;
	if ((float1 + float2) == 0) return false;
	if(float1 == 0) return std::abs(float2) < absolute_eps;
	if(float2 == 0) return std::abs(float1) < absolute_eps;
	return std::abs((float1 - float2) / (float1 + float2)) < relative_eps;
}

inline constexpr double pi = 3.1415926535897932384626433832795028841971693993751058209749;
inline constexpr double e = 2.71828182845904523536028747135266249775724709369995957496696;
