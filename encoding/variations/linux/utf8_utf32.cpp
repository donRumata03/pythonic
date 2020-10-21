//
// Created by Vova on 25.05.2020.
//

#include "linux_recoding_base.h"



namespace recode {
	/// utf8 <-> utf32
	std::string to_utf8(const std::wstring &utf32_string)
	{
        return recode_base<
                std::wstring,
                std::string,
                size_t(4)
                            >(utf32_string, "UTF32", "UTF8");
	}

	std::wstring from_utf8_to_utf32(const std::string &utf8_string)
	{
		return recode_base<
                std::string,
                std::wstring,
                1
        >(utf8_string, "UTF8", "UTF32");
	}
}
