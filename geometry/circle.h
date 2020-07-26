//
// Created by Vova on 27.05.2020.
//

#pragma once


#include <ostream>
#include "point.h"

struct circle
{
	point center;
	double r = 0;

	circle(const point& p, double radius) : center{p}, r{radius} {}
	// circle(const std::pair<double, double>& p, double radius) : center{p}, r{radius} {}
	circle(const point& cent, const point& circle_point) : center{cent}, r {point::dist(center, circle_point)} {}
	circle(const point& p1, const point& p2, const point& p3);

	circle(const circle& other) = default;

	friend bool operator == (const circle& p1, const circle& p2);

	friend std::ostream &operator<<(std::ostream &os, const circle &circle);
};


