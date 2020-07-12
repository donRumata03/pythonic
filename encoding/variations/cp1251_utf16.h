//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <string>

namespace recode {
	/// cp1251 <-> utf16
	std::string to_cp1251(const std::wstring &utf16_string);                // Throws exception (encode_exception)
	std::wstring from_cp1251_to_utf16(const std::string &cp1251_string);    // Throws exception (encode_exception)
}
