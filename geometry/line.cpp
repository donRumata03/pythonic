//
// Created by Vova on 26.05.2020.
//

#include <cassert>
#include "line.h"

line::line(double A, double B, double C) : A(A), B(B), C(C)
{}

line::line(double k, double b)
{
	A = k;
	B = -1;
	C = b;
}

line::line(const point &point1, const point &point2)
{
	if (point1.x != point2.x)
	{
		double k = (point2.y - point1.y) / (point2.x - point1.x);
		double b = point1.y - point1.x * k;
		*this = line(k, b);
	}
	else
	{
		B = 0;

		double x = point1.x; // <- = point2.x
		// x = -C/A
		// A = 1
		A = 1;
		C = -x;
	}
}

double line::get_A() const
{
	return A;
}

double line::get_B() const
{
	return B;
}

double line::get_C() const
{
	return C;
}

std::ostream &operator<<(std::ostream &os, const line &line)
{
	os << "Line: { " << "A: " << line.A << " B: " << line.B << " C: " << line.C << " }";
	return os;
}

double line::operator()(double x) const
{
	assert(B != 0);
	return -(A * x + C) / B;
}





