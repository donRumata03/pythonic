//
// Created by Vova on 26.05.2020.
//

#pragma once


#include <ostream>
#include "point.h"

class line
{
	double A = 0;
	double B = 0;
	double C = 0;

public:
	[[nodiscard]] double get_A() const;

	[[nodiscard]] double get_B() const;

	[[nodiscard]] double get_C() const;

public:
	line(double A, double B, double C);
	line(double k, double b);

	line(const point& point1, const point& point2);

	friend std::ostream &operator<<(std::ostream &os, const line &line);
	double operator() (double x) const;
};


