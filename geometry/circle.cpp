//
// Created by Vova on 27.05.2020.
//

#include "pch.h"
#include "circle.h"

circle::circle(const point &p1, const point &p2, const point &p3)
{
	// 2x * (x_2 - x_1) = 2y(y_1 - y_2) + x_2^2 + y_2^2 - x_1^2 - y_1^2
	// x = (2y(y_1 - y_2) + x_2^2 + y_2^2 - x_1^2 - y_1^2) / (2(x_2 - x_1))

	// 2x * (x_3 - x_2) = 2y(y_2 - y_3) + x_3^2 + y_3^2 - x_2^2 - y_2^2
	// x = (2y(y_2 - y_3) + x_3^2 + y_3^2 - x_2^2 - y_2^2) / (2(x_3 - x_2))
	// (2y(y_1 - y_2) + x_2^2 + y_2^2 - x_1^2 - y_1^2) / (2(x_2 - x_1)) = (2y(y_2 - y_3) + x_3^2 + y_3^2 - x_2^2 - y_2^2) / (2(x_3 - x_2))

	// y * ( (y1 - y2) / (x2 - x1) - (y2 - y3) / (x3 - x2) ) = (square(x3) + square(y3) - square(x2) - square(y2)) / (2 * (x3 - x2)) -
	//						(square(x2) + square(y2) - square(x1) - square(y1)) / (2 * (x2 - x1))

	assert(p1 != p2 && p1 != p3 && p2 != p3);

	double x1 = p1.x;
	double y1 = p1.y;

	double x2 = p2.x;
	double y2 = p2.y;

	double x3 = p3.x;
	double y3 = p3.y;

	double y_mul = (y1 - y2) / (x2 - x1) - (y2 - y3) / (x3 - x2);
	double right_part = (square(x3) + square(y3) - square(x2) - square(y2)) / (2 * (x3 - x2)) -
						(square(x2) + square(y2) - square(x1) - square(y1)) / (2 * (x2 - x1));

	double center_y = right_part / y_mul;
	double center_x = (2 * center_y * (y1 - y2) + square(x2) + square(y2) - square(x1) - square(y1)) / (2 * (x2 - x1));

	center = {center_x, center_y};
	r = point::dist(center, p1);
}

std::ostream &operator<<(std::ostream &os, const circle &circle)
{
	os << "Circle: { center: " << circle.center << ", r: " << circle.r << " }";
	return os;
}

bool operator==(const circle &c1, const circle &c2)
{
	return c1.center == c2.center && c1.r == c2.r;
}
