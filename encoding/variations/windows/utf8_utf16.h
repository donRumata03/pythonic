//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <string>

namespace recode {
/// utf8 <-> utf16
	std::string to_utf8(const std::wstring &utf16_string);                  // Throws exception (win32::Utf8ConversionException)!
	std::wstring from_utf8_to_utf16(const std::string &utf8_string);        // Throws exception (win32::Utf8ConversionException)!

}
