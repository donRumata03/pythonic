//
// Created by Vova on 25.05.2020.
//

#include "encode_exception.h"

encode_exception::encode_exception(
		const char* const message,
		const uint32_t errorCode,
		const conversion_type type)

		: std::runtime_error(message)
		, _errorCode(errorCode)
		, _conversionType(type)
{
}


inline encode_exception::encode_exception(
		const std::string& message,
		const uint32_t errorCode,
		const conversion_type type)

		: std::runtime_error(message)
		, _errorCode(errorCode)
		, _conversionType(type)
{
}


inline uint32_t encode_exception::ErrorCode() const
{
	return _errorCode;
}


inline encode_exception::conversion_type encode_exception::Direction() const
{
	return _conversionType;
}
