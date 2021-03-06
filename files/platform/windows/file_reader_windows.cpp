//
// Created by Vova on 24.05.2020.
//

#include "pythonic_pch.h"

#include "file_reader_windows.h"
#include "encoding/encoder.h"
#include "files/file_reader_base.h"

// #include "encoding/win32_examples/utf8_utf16_conversion.h"




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

/*
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
*/


std::optional<std::string> read_file(const std::filesystem::path& filename) {
	return read_file(recode::from_utf8_to_utf16(filename.string()));
}

void write_file(const std::string& data, const std::filesystem::path& filename) {
	write_file(data, recode::from_utf8_to_utf16(filename.string()));
}

void file_size_in_bytes(const std::filesystem::path& filename) {
	file_size_in_bytes(recode::from_utf8_to_utf16(filename.string()));
}





std::optional<std::string> read_file (const std::wstring &filename)
{
	return base_read_file(filename);
}

void write_file (const std::string &data, const std::wstring &filename)
{
	return base_write_file(data, filename);
}

uint64_t file_size_in_bytes (const std::wstring &filename)
{
	return base_file_size_in_bytes(filename);
}

