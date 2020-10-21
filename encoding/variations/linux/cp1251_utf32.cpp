//
// Created by Vova on 25.05.2020.
//

#include <encoding/encode_exception.h>
#include "cp1251_utf32.h"
#include "linux_recoding_base.h"


namespace recode {
	/// cp1251 <-> utf16
	std::string to_cp1251(const std::wstring &utf32_string)
	{
        return recode_base<std::wstring, std::string, size_t(1)>(utf32_string, "UTF32", "UTF32");
	}

	std::wstring from_cp1251_to_utf32(const std::string &cp1251_string)
	{
		return {};
	}
}
