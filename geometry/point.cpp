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


//////////// Element-wise operators: //////////////////

point operator+ (const point &first, const point &second)
{
	return point { first.x + second.x, first.y + second.y };
}

point operator- (const point &first, const point &second)
{
	return point { first.x - second.x, first.y - second.y };
}

point operator* (const point &first, const point &second)
{
	return point { first.x * second.x, first.y * second.y };
}

point operator/ (const point &first, const point &second)
{
	return point { first.x / second.x, first.y / second.y };
}

point sqrt (const point &point)
{
	return { std::sqrt(point.x), std::sqrt(point.y) };
}

point pow (const point &point, double pow)
{
	return { std::pow(point.x, pow), std::pow(point.y, pow) };
}












/*
bool operator==(const point &p1, const point &p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}
*/
