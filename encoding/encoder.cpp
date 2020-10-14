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


/*

static Letter g_letters[] = {
		{static_cast<char>(0x82), 0x201A}, // SINGLE LOW-9 QUOTATION MARK
		{static_cast<char>(0x83), 0x0453}, // CYRILLIC SMALL LETTER GJE
		{static_cast<char>(0x84), 0x201E}, // DOUBLE LOW-9 QUOTATION MARK
		{static_cast<char>(0x85), 0x2026}, // HORIZONTAL ELLIPSIS
		{static_cast<char>(0x86), 0x2020}, // DAGGER
		{0x87, 0x2021}, // DOUBLE DAGGER
		{0x88, 0x20AC}, // EURO SIGN
		{0x89, 0x2030}, // PER MILLE SIGN
		{0x8A, 0x0409}, // CYRILLIC CAPITAL LETTER LJE
		{0x8B, 0x2039}, // SINGLE LEFT-POINTING ANGLE QUOTATION MARK
		{0x8C, 0x040A}, // CYRILLIC CAPITAL LETTER NJE
		{0x8D, 0x040C}, // CYRILLIC CAPITAL LETTER KJE
		{0x8E, 0x040B}, // CYRILLIC CAPITAL LETTER TSHE
		{0x8F, 0x040F}, // CYRILLIC CAPITAL LETTER DZHE
		{0x90, 0x0452}, // CYRILLIC SMALL LETTER DJE
		{0x91, 0x2018}, // LEFT SINGLE QUOTATION MARK
		{0x92, 0x2019}, // RIGHT SINGLE QUOTATION MARK
		{0x93, 0x201C}, // LEFT DOUBLE QUOTATION MARK
		{0x94, 0x201D}, // RIGHT DOUBLE QUOTATION MARK
		{0x95, 0x2022}, // BULLET
		{0x96, 0x2013}, // EN DASH
		{0x97, 0x2014}, // EM DASH
		{0x99, 0x2122}, // TRADE MARK SIGN
		{0x9A, 0x0459}, // CYRILLIC SMALL LETTER LJE
		{0x9B, 0x203A}, // SINGLE RIGHT-POINTING ANGLE QUOTATION MARK
		{0x9C, 0x045A}, // CYRILLIC SMALL LETTER NJE
		{0x9D, 0x045C}, // CYRILLIC SMALL LETTER KJE
		{0x9E, 0x045B}, // CYRILLIC SMALL LETTER TSHE
		{0x9F, 0x045F}, // CYRILLIC SMALL LETTER DZHE
		{0xA0, 0x00A0}, // NO-BREAK SPACE
		{0xA1, 0x040E}, // CYRILLIC CAPITAL LETTER SHORT U
		{0xA2, 0x045E}, // CYRILLIC SMALL LETTER SHORT U
		{0xA3, 0x0408}, // CYRILLIC CAPITAL LETTER JE
		{0xA4, 0x00A4}, // CURRENCY SIGN
		{0xA5, 0x0490}, // CYRILLIC CAPITAL LETTER GHE WITH UPTURN
		{0xA6, 0x00A6}, // BROKEN BAR
		{0xA7, 0x00A7}, // SECTION SIGN
		{0xA8, 0x0401}, // CYRILLIC CAPITAL LETTER IO
		{0xA9, 0x00A9}, // COPYRIGHT SIGN
		{0xAA, 0x0404}, // CYRILLIC CAPITAL LETTER UKRAINIAN IE
		{0xAB, 0x00AB}, // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
		{0xAC, 0x00AC}, // NOT SIGN
		{0xAD, 0x00AD}, // SOFT HYPHEN
		{0xAE, 0x00AE}, // REGISTERED SIGN
		{0xAF, 0x0407}, // CYRILLIC CAPITAL LETTER YI
		{0xB0, 0x00B0}, // DEGREE SIGN
		{0xB1, 0x00B1}, // PLUS-MINUS SIGN
		{0xB2, 0x0406}, // CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I
		{0xB3, 0x0456}, // CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I
		{0xB4, 0x0491}, // CYRILLIC SMALL LETTER GHE WITH UPTURN
		{0xB5, 0x00B5}, // MICRO SIGN
		{0xB6, 0x00B6}, // PILCROW SIGN
		{0xB7, 0x00B7}, // MIDDLE DOT
		{0xB8, 0x0451}, // CYRILLIC SMALL LETTER IO
		{0xB9, 0x2116}, // NUMERO SIGN
		{0xBA, 0x0454}, // CYRILLIC SMALL LETTER UKRAINIAN IE
		{0xBB, 0x00BB}, // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
		{0xBC, 0x0458}, // CYRILLIC SMALL LETTER JE
		{0xBD, 0x0405}, // CYRILLIC CAPITAL LETTER DZE
		{0xBE, 0x0455}, // CYRILLIC SMALL LETTER DZE
		{0xBF, 0x0457} // CYRILLIC SMALL LETTER YI
};

*/

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


void set_utf8 ()
{
	SetConsoleOutputCP(CP_UTF8);
}
