//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <unordered_map>
#include <string>

#include <iostream>

enum class console_colors
{
	simple,
	red,
	purple,
	cyan,
	dark_cyan,
	blue,
	green,
	yellow,
	bold,
	underlined,
};


inline std::unordered_map<console_colors, std::pair<std::string, std::string> > console_color_recogniser =
		{
				{console_colors::simple,     {"",         ""}},

				{console_colors::red,        {"\x1B[31m", "\033[0m"}},
				{console_colors::purple,     {"\033[95m", "\033[0m"}},
				{console_colors::cyan,       {"\033[96m", "\033[0m"}},
				{console_colors::dark_cyan,  {"\033[36m", "\033[0m"}},
				{console_colors::blue,       {"\033[94m", "\033[0m"}},
				{console_colors::green,      {"\033[92m", "\033[0m"}},
				{console_colors::yellow,     {"\033[93m", "\033[0m"}},

				{console_colors::bold,       {"\033[1m",  "\033[0m"}},
				{console_colors::underlined, {"\033[4m",  "\033[0m"}},
		};

inline std::ostream& operator<<(std::ostream& stream, const console_colors& color) {
	if (color == console_colors::simple) {
		stream << "\033[0m";
	}
	else {
		stream << console_color_recogniser[color].first;
	}
	return stream;
}

inline void colored_print(const std::string& message, console_colors c){
	std::cout << console_color_recogniser[c].first;
	std::cout << message << std::endl;
	std::cout << console_color_recogniser[c].second;
}

template <class ... Args>
void colored_print(const std::string& message, console_colors c0, Args... args){
	std::cout << console_color_recogniser[c0].first;
	colored_print(message, args...);
	std::cout << console_color_recogniser[c0].second;
}
