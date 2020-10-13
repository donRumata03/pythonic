//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <string>

namespace recode {
	/// cp1251 <-> utf8
	std::string to_utf8(const std::string &cp1251_string);                  // Throws exception (encode_exception win32::Utf8ConversionException)
	std::string to_cp1251(const std::string &utf8_string);                  // Throws exception (encode_exception and win32::Utf8ConversionException)
}
