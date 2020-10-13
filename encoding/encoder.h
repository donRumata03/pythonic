//
// Created by Vova on 24.05.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "encode_exception.h"

#ifdef PYTHONIC_IS_WINDOWS
    #include "variations/windows/cp1251_utf16.h"
    #include "variations/windows/cp1251_utf8.h"
    #include "variations/windows/utf8_utf16.h"
    #include "encoding/win32_examples/utf8_utf16_conversion.h"
#elif defined(PYTHONIC_IS_LINUX)
    #include "variations/linux/cp1251_utf16.h"
    #include "variations/linux/cp1251_utf8.h"
    #include "variations/linux/utf8_utf16.h"
#else
        #error "Windows or Linux?"
#endif

#include <iostream>

void set_utf8_in_console();

enum class encoding
{
	utf8,
	cp1251,
	// utf16,
	any,    // This is an ASCII string, so, to convert it to any encoding, simply return it!
};

inline std::ostream& operator<< (std::ostream& out, /*const */ encoding/*&*/ enc) {

	switch (enc){
		using ::encoding;
		case encoding::utf8:
			out << std::string("Encoding: utf-8");
			break;
		case encoding::cp1251:
			out << std::string("Encoding: cp1251");
			break;
		case encoding::any:
			out << std::string("Encoding: any");
			break;
	}

	return out;
}



// Make one recode function? But which type?.

namespace recode
{
	/// Encoding determination:
	bool is_only_ASCII(const std::string &string);
	// bool is_valid_utf8(const char *string);
	bool is_valid_utf8(const std::string &string);
	bool is_valid_utf16(const std::string &some_string);

	encoding determine_encoding(const std::string &some_string);

	std::string auto_recode(const std::string& string, encoding target_encoding);
}

