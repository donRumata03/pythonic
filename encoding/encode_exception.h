//
// Created by Vova on 25.05.2020.
//

#pragma once


#include <cstdint>   // for uint32_t
#include <stdexcept>  // for std::runtime_error
#include <string>     // for std::string


class encode_exception : public std::runtime_error
{
public:
	enum class conversion_type
	{
		utf8_to_cp1251 = 0,
		utf16_to_cp1251,

		cp1251_to_utf8,
		cp1251_to_utf16
	};


	// Initialize with error message raw C-string, last Win32 error code and conversion direction
	encode_exception(const char* message, uint32_t errorCode, conversion_type type);

	// Initialize with error message string, last Win32 error code and conversion direction
	encode_exception(const std::string& message, uint32_t errorCode, conversion_type type);

	// Retrieve error code associated to the failed conversion
	[[nodiscard]] uint32_t ErrorCode() const;

	// Direction of the conversion (e.g. from UTF-8 to UTF-16)
	[[nodiscard]] conversion_type Direction() const;


private:
	// Error code from GetLastError()
	uint32_t _errorCode;

	// Direction of the conversion
	conversion_type _conversionType;
};



