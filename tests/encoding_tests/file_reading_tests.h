//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <encoding/encoder.h>

#include <pythonic.h>

#include <string>

using namespace recode;

inline void test_utf8_utf16_russian_file_writing()
{
#ifdef PYTHONIC_IS_WINDOWS

	std::string utf8_string = "Привет, мир!";

	std::wstring utf16_string = win32::Utf8ToUtf16(utf8_string);

	std::cout << utf8_string << std::endl;

	std::cout << "Input (utf8 string) size: " << utf8_string.size() << std::endl;
	std::cout << "Output (utf16 string) size: " << utf16_string.size() << std::endl;

	// Output the utf16-encoded result to a file:
	std::string out_filename = R"(D:\Projects\Tests\enc_test\utf16_example_output.txt)";

	const wchar_t* utf16_chars = utf16_string.c_str();
	size_t utf16_string_size = utf16_string.size();

	const char* utf16_mem = reinterpret_cast<const char*>(utf16_chars);

	std::ofstream out_file(out_filename);

	out_file.write(utf16_mem, utf16_string_size * 2);
	out_file.close();

#endif
}

inline void test_writing_file_with_russian_name()
{
#ifdef PYTHONIC_IS_WINDOWS

	std::string utf8_encoded_filename = R"(D:\Projects\Tests\enc_test\русская_папка\русский_файл.txt)";
	std::cout << utf8_encoded_filename << std::endl;

	std::wstring utf16_string = win32::Utf8ToUtf16(utf8_encoded_filename);

	std::string new_file_contents = "Тестовый файл с именем в кодировке utf16.";

	std::ofstream out_file(utf16_string);
	out_file << new_file_contents;
	out_file.close();
#endif
}


inline void test_reading_file_with_russian_name()
{
#ifdef PYTHONIC_IS_WINDOWS

	std::string utf8_encoded_filename = R"(D:\Projects\Tests\enc_test\русская_папка\файл с utf8 но руссим именем.txt)";
	std::cout << "Trying to read a file with name: " << utf8_encoded_filename << std::endl;

	std::wstring utf16_filename = win32::Utf8ToUtf16(utf8_encoded_filename);

	auto reading_try = read_file(utf16_filename);

	if (!reading_try){
		std::cout << "Failed to open file!" << std::endl;
		return;
	}

	std::string file_data = reading_try.value();

	std::cout << "File data: " << file_data << std::endl;
#endif
}

