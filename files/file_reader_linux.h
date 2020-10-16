//
// Created by Vova on 14.10.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "file_reader_base.h"
#include "encoding/encoder.h"

/// With recoding:

template<given_filename_encoding filename_encoding>
static std::string recode_filename_to_utf8(const std::string& filename) {
	if constexpr (filename_encoding == given_filename_encoding::utf8) {
		return filename;
	}
	else { // CP1251
		return recode::to_utf8(filename);
	}
}

template<given_filename_encoding filename_encoding>
std::optional<std::string> read_file (const std::string &filename)
{
	return base_read_file(recode_filename_to_utf8<filename_encoding>(filename));
}

template<given_filename_encoding filename_encoding>
void write_file (const std::string &data, const std::string &filename)
{
	return base_write_file(data, recode_filename_to_utf8<filename_encoding>(filename));
}

template<given_filename_encoding filename_encoding>
uint64_t file_size_in_bytes (const std::string &filename)
{
	return base_file_size_in_bytes(recode_filename_to_utf8<filename_encoding>(filename));
}



