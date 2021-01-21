//
// Created by Vova on 26.05.2020.
//

#pragma once


#include "pythonic_pch.h"
#include <maths/simple_functions.h>

struct point
{
	double x = 0;
	double y = 0;


	point() = default;
	point(double x, double y);
	/*explicit*/ point(const std::pair<double, double>& pair) : x(pair.first), y(pair.second) {}


	point(const point& other) = default;
	point(point&& other) = default;

	point& operator= (const point& other) = default;
	point& operator= (point&& other) = default;

	// friend bool operator == (const point& p1, const point& p2) = default;
	auto operator <=>(const point& other) const = default;

	double& operator[] (size_t index) { assert(index == 0 || index == 1); return reinterpret_cast<double*>(this)[index]; }
	const double& operator[] (size_t index) const { return const_cast<const double&>(const_cast<point*>(this)->operator[](index)); }

	friend std::ostream &operator<<(std::ostream &os, const point &point);
	/*explicit*/ operator std::pair<double, double> () const { return { x, y }; }

	static double sqr_dist(const point& p1, const point& p2) { return square(p1.x - p2.x) + square(p1.y - p2.y); }
	static double dist(const point& p1, const point& p2) { return sqrt(sqr_dist(p1, p2)); }

	double sqr_module() const { return square(x) + square(y); }
	double module() const { return std::sqrt(sqr_module()); }

	[[nodiscard]] bool is_zero() const { return x == 0. and y == 0.; }

	point & scale_from (const point &from_what, double scale_factor);
	point& scale_x_from(double from, double scale_factor);
	point& scale_y_from(double from, double scale_factor);
};

/// Json

void to_json(json& j, const point& point);
void from_json(const json& j, point& point);


/// Operators:

point operator- (const point& point);

point operator+ (const point& first, const point& second);
point operator- (const point& first, const point& second);
point operator* (const point& first, const point& second);
point operator/ (const point& first, const point& second);

point operator+ (const point& point, double value);
point operator+ (double value, const point& point);

point operator- (const point& point, double value);
point operator- (double value, const point& point);

point operator* (const point& point, double value);
point operator* (double value, const point& point);

point operator/ (const point& point, double value);


double dot_product(const point& point1, const point& point2);
bool are_perpendicular(const point& point1, const point& point2);

double cross_product(const point& point1, const point& point2);




point sqrt(const point& point);
point pow(const point& point, double pow);
point log(const point& point, double log_base);

double abs(const point& point);
double squared_abs(const point& point);
