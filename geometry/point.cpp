//
// Created by Vova on 26.05.2020.
//

#include "point.h"

point::point(double x, double y) : x(x), y(y)
{}

std::ostream &operator<<(std::ostream &os, const point &point)
{
	os << "Point: { " << "x: " << point.x << " y: " << point.y << " }";
	return os;
}

/*
bool operator==(const point &p1, const point &p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}
*/
