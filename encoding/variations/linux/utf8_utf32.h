//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <string>

namespace recode {
/// utf8 <-> utf16
	std::string to_utf8(const std::wstring &utf32_string);                  // Throws exception!
	std::wstring from_utf8_to_utf32(const std::string &utf8_string);        // Throws exception!

}
