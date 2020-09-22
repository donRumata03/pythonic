//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <unordered_map>
#include <string>

#include <iostream>

enum class console_colors
{
	remove_last_color,
	remove_all_colors,
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

inline size_t applied_console_color_counter = 0;

constexpr const char* color_ending_string = "\033[0m";
static inline std::unordered_map<console_colors, std::string> console_color_recogniser =
		{
				{console_colors::remove_last_color, "\033[0m"},

				{console_colors::red,               "\x1B[31m" },
				{console_colors::purple,            "\033[95m" },
				{console_colors::cyan,              "\033[96m" },
				{console_colors::dark_cyan,         "\033[36m" },
				{console_colors::blue,              "\033[94m" },
				{console_colors::green,             "\033[92m" },
				{console_colors::yellow,            "\033[93m" },

				{console_colors::bold,              "\033[1m" },
				{console_colors::underlined,        "\033[4m" },
		};

inline std::ostream& operator<<(std::ostream& stream, const console_colors& color) {
	if (color == console_colors::remove_last_color) {
		if (applied_console_color_counter > 0)
			stream << color_ending_string;
	}
	else if (color == console_colors::remove_all_colors) {
		for (; applied_console_color_counter > 0; --applied_console_color_counter) {
			stream << color_ending_string;
		}
	}
	else {
		stream << console_color_recogniser[color];
		applied_console_color_counter++;
	}
	return stream;
}

inline void colored_print(const std::string& message, console_colors c){
	std::cout << c;
	std::cout << message << std::endl;
	std::cout << console_colors::remove_last_color;
}

template <class ... Args>
void colored_print(const std::string& message, console_colors c0, Args... args){
	std::cout << c0;
	colored_print(message, args...);
	std::cout << console_colors::remove_last_color;
}
