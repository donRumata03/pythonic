//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <files/file_reader.h>
#include <encoding/encoder.h>

#include <string>

using namespace recode;

inline void test_cp1251_file_writing(){
	std::string utf8_encoded_filename = R"(D:\Projects\Tests\enc_test\русская_папка\русский файл в кодировке cp1251.txt)";
	std::cout << "Trying to write file with name: " << utf8_encoded_filename << std::endl;

	// std::wstring utf16_filename = win32::Utf8ToUtf16(utf8_encoded_filename);

	std::string new_file_contents_utf8 = "Тестовый файл с текстом в кодировке cp1251.";

	std::string new_file_contents = recode::to_cp1251(new_file_contents_utf8);

	write_file<given_filename_encoding::utf8>(new_file_contents, utf8_encoded_filename);
	// std::ofstream out_file(utf16_filename);
	// out_file << new_file_contents;
	// out_file.close();
}

inline void test_cp1251_file_reading(){
	// std::string utf8_encoded_filename = R"(D:\Projects\Tests\enc_test\русская_папка\cp1251 содержимое.txt)";
	std::string utf8_encoded_filename = R"(D:\Literature_data\All_books\Толстой Лев\Война и мир Том 3 и 4\text.txt)";


	std::cout << "Trying to read file with name: " << utf8_encoded_filename << std::endl;

	// std::wstring utf16_filename = win32::Utf8ToUtf16(utf8_encoded_filename);

	auto filesystem_response = read_file<given_filename_encoding::utf8>(utf8_encoded_filename);

	if(!filesystem_response){
		std::cout << "Cannot read the file!" << std::endl;
		return;
	}

	std::string cp1251_file_content = *filesystem_response;

	std::string utf8_encoded_file_content = recode::to_utf8(cp1251_file_content);

	std::cout << "File contents: " << utf8_encoded_file_content << std::endl;
}

inline std::string test_to_cp1251(const std::string &utf8_string)
{
#ifdef PYTHONIC_IS_WINDOWS

	if (utf8_string.empty()) {

		return std::string();
	}

	int wide_char_len = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), utf8_string.size(), nullptr, 0);

	if (wide_char_len > 0 && wide_char_len != 0xFFFD) {
		std::vector<wchar_t> w_buf(wide_char_len);
		MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), utf8_string.size(), &w_buf[0], wide_char_len);
		std::vector<char> buf(wide_char_len);

		char default_char = 0;

		WideCharToMultiByte
				(
						1251,
						0,
						&w_buf[0],
						wide_char_len,
						&buf[0],
						wide_char_len,
						&default_char,
						nullptr
				);

		return std::string(&buf[0], wide_char_len);
	}
#endif
	return std::string();
}

inline void test_converting_bad_unicode_characters_to_cp1251(){
	std::string s = "Привет, ರೃೃ, ведь солнце светит!";

	std::cout << s << std::endl;

	std::wstring encoded_filename = recode::from_utf8_to_utf16(R"(D:\Projects\Tests\enc_test\русская_папка\bad_characters_cp1251.txt)");
	std::cout << "Encoded filename!" << std::endl;

	std::string cp1251_encoded;
	try {
		cp1251_encoded = recode::to_cp1251(s);
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	for(auto& i : cp1251_encoded) std::cout << int(i) << std::endl;

	std::cout << recode::to_utf8(cp1251_encoded) << std::endl;

	std::cout << "Encoded string!" << std::endl;



	write_file(cp1251_encoded, encoded_filename);
}

inline void lang_recognition_test(){
	std::string russian_string = recode::to_cp1251("Ёривет, мир!");
	std::string english_string = recode::to_cp1251("Hello, world!");

	std::cout << is_english_letter(russian_string[0]) << " " << is_russian_letter(russian_string[0]) << std::endl;
	std::cout << is_english_letter(english_string[0]) << " " << is_russian_letter(english_string[0]) << std::endl;

	// Bad!!!:

	std::cout << isalnum(to_cp1251("п")[0]) << std::endl;

	std::cout << "_________________" << std::endl;

	char test_char = '.';

	std::cout << is_from_word(test_char) << std::endl;
	std::cout << isdigit(test_char) << " " << is_english_letter(test_char) << " " << is_russian_letter(test_char) << std::endl;

	print(is_russian_letter('\xef'));
	print(is_english_letter('\xef'));
	/// print(isdigit('\xef')); <- Fails!!!
	print(is_from_word('\xef'));


}
