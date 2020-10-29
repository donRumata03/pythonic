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

point & point::scale_from (const point &from_what, double scale_factor)
{
	(*this) = (*this) + ((*this) - from_what) * (scale_factor - 1);
	return *this;
}

point &point::scale_x_from (double from, double scale_factor)
{
	x += (x - from) * (scale_factor - 1);
	return *this;
}

point &point::scale_y_from (double from, double scale_factor)
{
	y += (y - from) * (scale_factor - 1);
	return *this;
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



point operator+ (const point &point, double value)
{
	return { point.x + value, point.y + value };
}

point operator+ (double value, const point &point)
{
	return point + value;
}


point operator- (const point &point, double value)
{
	return { point.x - value, point.y - value };
}

point operator- (double value, const point &point)
{
	return { value - point.x, value - point.y };
}

point operator* (const point &point, double value)
{
	return { point.x * value, point.y * value };
}

point operator* (double value, const point &point)
{
	return point * value;
}

point operator/ (const point &point, double value)
{
	return { point.x / value, point.y / value };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

point sqrt (const point &point)
{
	return { std::sqrt(point.x), std::sqrt(point.y) };
}

point pow (const point &point, double pow)
{
	return { std::pow(point.x, pow), std::pow(point.y, pow) };
}


point log (const point &point, double log_base)
{
	double log_of_log_base = std::log(log_base);
	return { std::log(point.x) / log_of_log_base, std::log(point.y) / log_of_log_base };
}

double abs (const point &point)
{
	return std::sqrt(squared_abs(point));
}

double squared_abs (const point &point)
{
	return square(point.x) + square(point.y);
}

////////////////////////////////////////////////////////////////////////

void to_json (json& j, const point& point)
{
	j["x"] = point.x;
	j["y"] = point.y;
}

void from_json (const json& j, point& point)
{
	point.x = j["x"];
	point.y = j["y"];
}













/*
bool operator==(const point &p1, const point &p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}
*/
