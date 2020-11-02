//
// Created by Vova on 14.10.2020.
//

#include "file_reader_linux.h"


std::optional<std::string> read_file(const std::filesystem::path& filename) {
	return read_file<given_filename_encoding::utf8>(filename.string());
}

void write_file(const std::string& data, const std::filesystem::path& filename) {
	write_file<given_filename_encoding::utf8>(data, filename.string());
}

void file_size_in_bytes(const std::filesystem::path& filename) {
	file_size_in_bytes<given_filename_encoding::utf8>(filename.string());
}


