//
// Created by Vova on 27.05.2020.
//

#pragma once

#include <ostream>
#include "other/python_builtins.h"
#include "maths/numpyic.h"

#include <displaying/type_printer.h>

template<class T> class nd_point
{
	std::vector<T> dimensions;
	size_t dimension_number;

public:
	explicit nd_point(size_t dimensions_number = 2) : dimension_number{dimensions_number} {
		dimensions.resize(dimension_number);
	}

	nd_point(const nd_point<T>& other) = default;
	nd_point(nd_point<T>&& other) noexcept = default;
	nd_point<T>& operator= (nd_point<T>&& other) noexcept = default;
	nd_point<T>& operator= (const nd_point<T>& other) = default;

	explicit nd_point(const std::vector<T>& dims_data) {
		dimensions = dims_data;
		dimension_number = dimensions.size();
	}

	T& operator[] (size_t dim_index) { return dimensions[dim_index]; }

	template <class Tt> friend nd_point<Tt> operator+ (const nd_point<Tt>& point1, const nd_point<Tt>& point2);

	[[nodiscard]] const std::vector<T>& get_dimension_data() const {
		return dimensions;
	}
	[[nodiscard]] size_t get_dimension_number() const { return dimension_number; }

	template <class Tt> friend std::ostream &operator<<(std::ostream &os, const nd_point<Tt> &point);
};

template <class T> nd_point<T> operator+(const nd_point<T>& point1, const nd_point<T>& point2)
{
	assert(point1.dimension_number == point2.dimension_number);
	return nd_point{ element_wise_sum(point1.dimensions, point2.dimensions) };
}


template <class T> std::ostream &operator<<(std::ostream &os, const nd_point<T> &point)
{
	os << "Nd_Point <" << type_name<T>() << "> : { " << "dimensions: " << point.dimensions << ", dimension_number: " << point.dimension_number << " }";
	return os;
}

