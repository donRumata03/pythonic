//
// Created by Vova on 26.05.2020.
//

#pragma once


#include <ostream>
#include <maths/simple_functions.h>

struct point
{
	double x = 0;
	double y = 0;

	point(double x, double y);
	point() = default;

	point(const point& other) = default;

	friend bool operator == (const point& p1, const point& p2);
	double& operator[] (size_t index) { assert(index == 0 || index == 1); return reinterpret_cast<double*>(this)[index]; }
	const double& operator[] (size_t index) const { return const_cast<const double&>(const_cast<point*>(this)->operator[](index)); }

	friend std::ostream &operator<<(std::ostream &os, const point &point);

	static double sqr_dist(const point& p1, const point& p2) { return square(p1.x - p2.x) + square(p1.y - p2.y); }
	static double dist(const point& p1, const point& p2) { return sqrt(sqr_dist(p1, p2)); }

	// template <class T, class E> point(const T& x, const E& y);
};


