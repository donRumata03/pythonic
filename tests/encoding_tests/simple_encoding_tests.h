//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <files/file_reader.h>
#include <encoding/encoder.h>

#include <string>
#include <encoding/variations/cp1251_utf8.h>

using namespace recode;

inline void simple_test_encoding(){
	std::string eng = "Hello!";
	std::string rus = "Привет";

	std::cout << eng.size() << " " << rus.size() << std::endl;

	std::cout << rus[0] << rus[1] << std::endl; // Russian symbols have 2 bytes!
}

inline void test_file_reading() {
	// std::string utf8_filename = R"(D:\Literature_data\All_books\Толстой Лев\Война и мир Том 3 и 4\text.txt)"; // This is encoded in utf8, so, literals are also!
	std::string utf8_filename = R"(D:\Projects\Video_anal\test_cp1251_text.txt)"; // This is encoded in utf8, so, literals are also!

	std::string cp1251_filename = to_cp1251(utf8_filename);

	std::cout << utf8_filename << ";" << cp1251_filename << std::endl;

	for(auto& c : cp1251_filename){
		std::cout << int(c) << std::endl;
	}

	auto r = read_file(cp1251_filename);

	if (!r) {
		std::cout << "Failed to read file! Check the filename encoding and if the assumed filename exists.\n";
		return;
	}

	auto s = *r;

	std::cout << s << ": " << std::endl;

	for(auto& c : s){
		std::cout << int(c) << std::endl;
	}

	// Opening file with read filename:

	auto rr = read_file(s);

	if (!rr) {
		std::cout << "Failed to read file! Check the filename encoding and if the assumed filename exists.\n";
		return;
	}

	std::cout << *rr << std::endl;

	return;


	std::cout << s << std::endl;

	for(auto& c : cp1251_filename){
		std::cout << int(c) << std::endl;
	}
}

inline void test_utf16_files(){
	std::string filename = R"(D:\Projects\Tests\enc_test\utf16_example.txt)"; // It`s a path to utf16-LE encoded file!

	std::wstring u16_filename = LR"(D:\Projects\Tests\enc_test\utf16_example.txt)";

	std::wcout << u16_filename << std::endl;

	// std::string file_data = *read_file(filename);

	// std::wstring file_contents(reinterpret_cast<const wchar_t*>(file_data.c_str(), file_data.size() / 2));

	// std::cout << "Real length: " << file_contents.size() << " symbols." << std::endl;

	// std::cout << "Raw view: \"" << *read_file(filename) << "\"" << std::endl;
	// std::wcout << "UCS2 wstring: \"" << reinterpret_cast<const wchar_t*>(file_data.c_str()) << "\"" << std::endl;
}

inline void test_utf8_utf16_english_converting()
{
	std::wstring s1u16 = L"Hello, world!";
	std::string s1u8 = win32::Utf16ToUtf8(s1u16);
	std::wstring s1u16back = win32::Utf8ToUtf16(s1u8);

	std::string to_print = win32::Utf16ToUtf8(s1u16back);


	std::cout << to_print << std::endl;
	std::wcout << s1u16back << std::endl;

}



