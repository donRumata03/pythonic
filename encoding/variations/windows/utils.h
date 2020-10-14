//
// Created by vova on 14.10.2020.
//

#pragma once
#include "pythonic_pch.h"

inline bool is_valid_utf16(const std::wstring &some_string)
{
    // TODO: implement through trying recoding from utf16 to utf8!
    return false;
}


inline bool is_valid_utf8(const std::string &string)
{
    // Try to convert to utf-16
    if (string.empty()) return true;

    int mx = std::numeric_limits<int>::max();
    if (string.size() > static_cast<size_t>(mx))
        return false; // Too long to understand;

    int input_length = static_cast<int>(string.size());

    const int utf16Length = ::MultiByteToWideChar(
            CP_UTF8,                        // source string is in UTF-8
            MB_ERR_INVALID_CHARS,           // conversion flags
            string.data(),                    // source UTF-8 string pointer
            input_length,                     // length of the source UTF-8 string, in chars
            nullptr,                        // unused - no conversion done in this step
            0                               // request size of destination buffer, in wchar_ts
    );

    return utf16Length != 0;
}

