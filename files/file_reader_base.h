//
// Created by vova on 14.10.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "encoding/encoder.h"

template<class FileNameType> std::string get_utf_string_from_generic_filename(const FileNameType& filename) {
	if constexpr (std::is_same_v<FileNameType, std::string>) {
		// Already utf8!
		return filename;
	}
	else if constexpr (std::is_same_v<FileNameType, std::wstring>) {
		// UTF-16 => convert to utf8:
		return recode::to_utf8(filename);
	}
	else if constexpr (std::is_same_v<FileNameType, std::filesystem::path>) {
		return filename.string();
	}
	else {
		static_assert(false, "Bad type");
	}
}


template<class FileSystemStringType>
std::optional<std::string> base_read_file(const FileSystemStringType &filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);

    if (in)
    {
        std::string contents;

        in.seekg(0, std::ios::end);
        contents.resize(static_cast<const unsigned int>(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }

//    std::string utf_recoded_filename;
//    if constexpr (std::is_same_v<std::string, FileSystemStringType>) {
//        // Linux => already in utf8
//        utf_recoded_filename = filename;
//    }
//    else {
//        utf_recoded_filename = recode::to_utf8(filename);
//    }
//
    std::cerr << "Failed to read file \"" << get_utf_string_from_generic_filename(filename) << "\": The file probably doesn`t exist!";

    return {};
}

template<class FileSystemStringType>
void base_write_file(const std::string &data, const FileSystemStringType &filename)
{
	std::ofstream out_file(filename);
	out_file << data;
	out_file.close();
}

template<class FileSystemStringType>
uint64_t base_file_size_in_bytes(const FileSystemStringType &filename)
{
	uint64_t beg;
	uint64_t end;
	std::ifstream f (filename);

	beg = f.tellg();
	f.seekg(0, std::ios::end);
	end = f.tellg();
	f.seekg(0, std::ios::beg);
	f.close();

	return end - beg;
}


////////////////////////////////////////////////////////////////////////

// Instantiate for fs::path:
inline auto read_file(const std::filesystem::path& filename) {
	return base_read_file(filename);
}

inline auto write_file(const std::string& data, const std::filesystem::path& filename) {
	base_write_file(data, filename);
}

inline auto file_size_in_bytes(const std::filesystem::path& filename) {
	return base_file_size_in_bytes(filename);
}

////////////////////////////////////////////////////////////////////////

enum class given_filename_encoding {
	cp1251,
	utf8
};

/// Define interface:
template<given_filename_encoding filename_encoding>
std::optional<std::string> read_file(const std::string &filename);

template<given_filename_encoding filename_encoding>
void write_file(const std::string &data, const std::string &filename);

template<given_filename_encoding filename_encoding>
uint64_t file_size_in_bytes(const std::string &filename);

