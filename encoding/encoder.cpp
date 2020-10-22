//
// Created by Vova on 24.05.2020.
//

#include "pythonic_pch.h"

#include <vector>
#include "encoder.h"



void set_utf8_in_console() {
#ifdef PYTHONIC_IS_WINDOWS
    SetConsoleOutputCP(CP_UTF8);
    system(("chcp "s + std::to_string(CP_UTF8)).c_str());
#endif
}

std::u8string as_u8string(std::string &utf8_encoded_string) {
    return reinterpret_cast<std::u8string&>(utf8_encoded_string);
}

std::u8string to_u8string(const std::string &utf8_encoded_string) {

    std::u8string res(
            reinterpret_cast<const char8_t*>(utf8_encoded_string.data()),
            utf8_encoded_string.size()
    ); // Copy

    return res; // Move
}


namespace recode
{
	/////////////////////////// 	Encoding determining:   /////////////////////////////////////

	encoding determine_encoding(const std::string &some_string)
	{
		if (some_string.empty()) return encoding::any;
		if (is_only_ASCII(some_string)) return encoding::any;

		if (is_valid_utf8(some_string)) return encoding::utf8;
		// else if (is_valid_utf16(some_string)) return encoding::utf16;
		else return encoding::cp1251;

		// return encoding::unknown;
	}



	bool is_only_ASCII(const std::string &string)
	{
		for(const auto& c : string) if (c < 0) return false; // a char > 0 <=> an unsigned char < 128; char = 0 => '\0' which is also OK for ASCII
		return true;
	}

	std::string auto_recode(const std::string &string, encoding target_encoding)
	{
	 	if (target_encoding == encoding::any) return string;
	 	auto real_encoding = determine_encoding(string);
		if (real_encoding == encoding::any || real_encoding == target_encoding) return string;

		if (real_encoding == encoding::cp1251) {
			if (target_encoding == encoding::utf8) {
				return to_utf8(string);
			}
		}

		else if (real_encoding == encoding::utf8){
			if (target_encoding == encoding::cp1251) {
				return to_cp1251(string);
			}
		}

		return "";
	}


/*
	std::string to_utf8(const std::string &cp1251_string)
	{
		return to_utf8(cp1251_string.c_str());
	}



	std::string to_utf8(const char *str)
	{
		std::string res;
		WCHAR *u_res = nullptr;
		char *c_res = nullptr;

		int result_u = MultiByteToWideChar(1251, 0, str, -1, nullptr, 0);
		if (result_u != 0) {
			u_res = new WCHAR[result_u];
			if (MultiByteToWideChar(1251, 0, str, -1, u_res, result_u)) {
				int result_c;
				result_c =
						WideCharToMultiByte(CP_UTF8,
						                    0,
						                    u_res,
						                    -1,
						                    nullptr,
						                    0,
						                    nullptr,
						                    nullptr
						);

				if (result_c != 0) {
					c_res = new char[result_c];
					if (WideCharToMultiByte(
							CP_UTF8,
							0,
							u_res,
							-1,
							c_res,
							result_c,
							nullptr,
							nullptr)) {
						res = c_res;
					}
				}
			}
		}

		delete[] u_res;
		delete[] c_res;

		return res;
	}

	*/



}
