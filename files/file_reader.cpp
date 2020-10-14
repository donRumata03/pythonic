//
// Created by Vova on 24.05.2020.
//

#include "pythonic_pch.h"

#include "file_reader.h"
#include "encoding/encoder.h"
// #include "encoding/win32_examples/utf8_utf16_conversion.h"


void write_file(const std::string &data, const std::wstring &filename)
{
	std::ofstream out_file(filename);
	out_file << data;
	out_file.close();
}

/*
std::optional<std::string> read_utf8_file_to_cp1251(const std::string &filename)
{
	auto file_read = read_file(filename);

	if (!file_read) {
		return std::optional<std::string>();
	}


	return {}; // to_cp1251(*file_read);
}
*/

std::optional<std::string> read_file(const std::string &utf8_filename)
{
	std::wstring utf16_filename;
	try{
		utf16_filename = win32::Utf8ToUtf16(utf8_filename);
	} catch(win32::Utf8ConversionException& exception) {
		std::cerr << "Failed to convert filename \"" << utf8_filename << "\" to utf16: " << exception.what() << std::endl;
		return std::optional<std::string>();
	}

	return read_file(utf16_filename);
}

uint64_t file_length(const std::wstring &filename)
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
