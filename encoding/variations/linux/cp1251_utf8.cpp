//
// Created by Vova on 25.05.2020.
//

#include "cp1251_utf8.h"

#include "linux_recoding_base.h"

//#include "cp1251_utf16.h"
//#include "utf8_utf16.h"

namespace recode
{
	/// cp1251 <-> utf8

	std::string to_utf8(const std::string &cp1251_string)
	{
		return recode_base<
		        std::string,
		        std::string,
		        size_t(1)>(cp1251_string, "CP2151", "UTF8");
		// return to_utf8(from_cp1251_to_utf16(cp1251_string));
	}

	std::string to_cp1251(const std::string &utf8_string)
	{
        return recode_base<
                std::string,
                std::string,
                size_t(1)>(utf8_string, "UTF8", "CP1251");

		// return to_cp1251(from_utf8_to_utf16(utf8_string));
	}
}
