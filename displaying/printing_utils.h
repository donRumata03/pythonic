//
// Created by Vova on 19.07.2021.
//

#pragma once

#include <pythonic_pch.h>

inline void display_delimiter() {
	std::cout << "_______________________________________________________________________" << std::endl;
}

/**
 * @param str — must be in ASCII
 * @return str with striking symbols
 *
 * @example «strikethrough» -> «s̶t̶r̶i̶k̶e̶t̶h̶r̶o̶u̶g̶h»
 */
inline std::string strike_text_through(const std::string& str) {
	std::string result;
	for (auto ch : str) {
//		result.append("\u0336");
		result.push_back(ch);
		result.append("̶");
	}
	return result;
}