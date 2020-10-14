//
// Created by Vova on 14.10.2020.
//

#pragma once

#include <string>

inline constexpr unsigned long long get_last_slash_index(const char* const string) {
	size_t res { 0 };

	const char * str_pnt = string;
	size_t index { 0 };
	while(*str_pnt) {
		if (*str_pnt == '\\' || *str_pnt == '/') {
			res = index;
		}
		str_pnt++;
		index++;
	}

	return res;
}

inline std::string get_path_folder(char* const child_filename) {
	/// D:/data/file.txt -> D:/data/
	/// D:\data\file.txt -> D:\data\

	// size_t last_slash_index = get_last_slash_index(child_filename);
	std::string res = child_filename;
	res.erase(res.begin() + res.find_last_of("\\/"), res.end());

	return res;
}

