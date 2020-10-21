//
// Created by Vova on 25.05.2020.
//

#include <encoding/encode_exception.h>
#include "cp1251_utf16.h"

#include "windows.h"

namespace recode {
	/// cp1251 <-> utf16
	std::string to_cp1251(const std::wstring &utf16_string)
	{
		// Result of the conversion
		std::string buffer_cp1251_string;

		// First, handle the special case of empty input string
		if (utf16_string.empty())
		{
			return buffer_cp1251_string;
		}

		// Safely fail if an invalid UTF-16 character sequence is encountered

		if (utf16_string.length() > static_cast<size_t>((std::numeric_limits<int>::max)()))
		{
			throw std::overflow_error(
					"Input string too long: size_t-length doesn't fit into int.");
		}
		const int input_length = static_cast<int>(utf16_string.length());

		char default_char = 0; // Also known as '\0';

		// Get the length, in chars, of the resulting cp1251 string
		const int output_length = ::WideCharToMultiByte(
				1251,               // convert to cp1251
				0,                     // conversion flags
				utf16_string.data(),        // source UTF-16 string
				input_length,               // length of source UTF-16 string, in wchar_ts
				nullptr,            // unused - no conversion required in this step
				0,                  // request size of destination buffer, in chars
				&default_char,              // Default char
				nullptr    // unused
		);

		if (output_length == 0)
		{
			// Conversion error: capture error code and throw
			const DWORD error = ::GetLastError();
			throw encode_exception(
					error == ERROR_NO_UNICODE_TRANSLATION ?
					"Invalid UTF-16 sequence found in input string."
					                                      :
					"Cannot get result string length when converting "\
            "from UTF-16 to cp1251 (WideCharToMultiByte failed).",
					error,
					encode_exception::conversion_type::utf16_to_cp1251);
		}

		buffer_cp1251_string.resize(output_length);


		// Do the actual conversion from CP1251 to UTF-16
		int result_size = ::WideCharToMultiByte(
				1251,                   // source string is in cp1251
				0,                      // no flags
				utf16_string.data(),    // source utf-16 string pointer
				input_length,           // length of source utf-16 string, in chars
				&buffer_cp1251_string[0],      // pointer to destination buffer
				output_length,          // size of destination buffer, in wchar_ts
				&default_char,           // Default char is '\0'
				nullptr
		);

		if (result_size == 0)
		{
			// Conversion error: capture error code and throw
			const DWORD error = ::GetLastError();
			throw encode_exception(
					error == ERROR_NO_UNICODE_TRANSLATION ?
					"Invalid UTF-16 sequence found in input string."
					                                      :
					"Cannot convert from UTF-16 to CP1251"\
                    "(WideCharToMultiByte failed).",
					error,
					encode_exception::conversion_type::cp1251_to_utf16);
		}

		// Now delete all zero characters
		std::string cp1251_string;
		cp1251_string.reserve(output_length);

		for(auto& c : buffer_cp1251_string) if (c) cp1251_string.push_back(c);

		// cp1251_string.shrink_to_fit(); but it`s probably useless!

		return cp1251_string;
	}

	std::wstring from_cp1251_to_utf32(const std::string &cp1251_string)
	{
		auto str = cp1251_string.c_str();

		// Result of the conversion
		std::wstring res;

		// First, handle the special case of empty input string
		if (cp1251_string.empty()){
			return res;
		}

		// Safely cast the length of the source UTF-8 string (expressed in chars)
		// from size_t (returned by std::string::length()) to int
		// for the MultiByteToWideChar API.
		// If the size_t value is too big to be stored into an int,
		// throw an exception to prevent conversion errors like huge size_t values
		// converted to *negative* integers.

		if (cp1251_string.length() > static_cast<size_t>((std::numeric_limits<int>::max)())){
			throw std::overflow_error(
					"Input string too long: size_t-length doesn't fit into int.");
		}

		const int input_length = static_cast<int>(cp1251_string.length());

		// Safely fail if an invalid UTF-8 character sequence is encountered
		constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;

		// Get the size of the destination UTF-16 string
		const int utf16Length = ::MultiByteToWideChar(
				1251,            // source string is in cp1251
				kFlags,                   // conversion flags
				str,                      // source UTF-8 string pointer
				input_length,             // length of the source UTF-8 string, in chars
				nullptr,      // unused - no conversion done in this step
				0              // request size of destination buffer, in wchar_ts
		);


		if (utf16Length == 0)
		{
			// Conversion error: capture error code and throw
			const DWORD error = ::GetLastError();
			throw encode_exception(
					error == ERROR_NO_UNICODE_TRANSLATION ?
					"Invalid cp1251 sequence found in input string. (?!?!...)"
					                                      :
					"Cannot get result string length when converting " \
            "from cp1251 to UTF-16 (MultiByteToWideChar failed).",
					error,
					encode_exception::conversion_type::cp1251_to_utf16);
		}


		res.resize(utf16Length);

		// Do the actual conversion from CP1251 to UTF-16
		int result_code = ::MultiByteToWideChar(
				1251,           // source string is in cp1251
				kFlags,                  // conversion flags
				cp1251_string.data(),    // source cp1251 string pointer
				input_length,            // length of source cp1251 string, in chars
				&res[0],     // pointer to destination buffer
				utf16Length              // size of destination buffer, in wchar_ts
		);
		if (result_code == 0)
		{
			// Conversion error: capture error code and throw
			const DWORD error = ::GetLastError();
			throw encode_exception(
					error == ERROR_NO_UNICODE_TRANSLATION ?
					"Invalid cp1251 sequence found in input string. (?!?!...)"
					                                      :
					"Cannot convert from CP1251 to UTF-16 "\
            "(MultiByteToWideChar failed).",
					error,
					encode_exception::conversion_type::cp1251_to_utf16);
		}

		return res;

		/*


			int result_size = MultiByteToWideChar(1251, 0, str, -1, nullptr, 0);
			if (result_size != 0) {
				u_res = new WCHAR[result_size];
				if (MultiByteToWideChar(1251, 0, str, -1, u_res, result_size)) {

					WideCharToMultiByte(CP_UTF8,
												0,
												u_res,
												-1,
												nullptr,
												0,
												nullptr,
												nullptr);
				}
			}

			res =

			return res;
		 */
	}
}
