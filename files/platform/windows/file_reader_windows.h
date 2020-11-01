//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <vector>
#include <optional>
#include <string>
#include <fstream>
#include <iostream>

#include "files/file_reader_base.h"

// Special for Windows:
std::optional<std::string> read_file(const std::wstring& filename);
void write_file(const std::string& data, const std::wstring& filename);
uint64_t file_size_in_bytes(const std::wstring& filename);

/// With recoding:

template<given_filename_encoding filename_encoding>
static std::wstring recode_filename_to_utf16(const std::string& filename) {
	if constexpr (filename_encoding == given_filename_encoding::utf8) {
		return recode::from_utf8_to_utf16(filename);
	}
	else {
		return recode::from_cp1251_to_utf16(filename);
	}
}

template<given_filename_encoding filename_encoding>
std::optional<std::string> read_file (const std::string &filename)
{
	return read_file(recode_filename_to_utf16<filename_encoding>(filename));
}

template<given_filename_encoding filename_encoding>
void write_file (const std::string &data, const std::string &filename)
{
	return write_file(data, recode_filename_to_utf16<filename_encoding>(filename));
}

template<given_filename_encoding filename_encoding>
uint64_t file_size_in_bytes (const std::string &filename)
{
	return file_size_in_bytes(recode_filename_to_utf16<filename_encoding>(filename));
}
