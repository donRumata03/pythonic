//
// Created by Vova on 25.05.2020.
//

#include "utf8_utf16.h"

#include "encoding/win32_examples/utf8_utf16_conversion.h"

namespace recode {
	/// utf8 <-> utf16
	std::string to_utf8(const std::wstring &utf16_string)
	{
		return win32::Utf16ToUtf8(utf16_string);
	}

	std::wstring from_utf8_to_utf16(const std::string &utf8_string)
	{
		return win32::Utf8ToUtf16(utf8_string);
	}
}
