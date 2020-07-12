//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <files/file_walker.h>
#include <displaying/byte_sizes/ByteSize.h>

inline void test_lsdir() {
	// std::string path0 = R"(D:\Projects\Tests\enc_test\русская_папка)";
	std::string path0 = R"(D:\Literature_data\All_books)";

	// Null terminating character exists!
	std::cout << int(path0[path0.size()]) << std::endl;

	auto response = recursive_lsdir(path0);

	for(auto& s : response) std::cout << s << std::endl;
}

inline void test_path_joining(){
	fs::path p (std::string("D:\\Literature_data\\All_books"));

	// fs::path p2 = p / "Толстой Лев" / "Анна Каренина" / "" / "";

	// std::cout << *read_file(p2.wstring()) << std::endl;
}

inline void test_file_size(){
	std::wstring w = recode::from_utf8_to_utf16(R"(D:\Projects\Tests\enc_test\русская_папка\bad_characters_cp1251.txt)");
	std::cout << fs_file_size(recode::to_utf8(w)) << std::endl;
}

inline void test_folder_size()
{
	// std::wstring w = from_utf8_to_utf16(R"(D:\Projects\Tests\enc_test\русская_папка)");
	std::wstring w = from_utf8_to_utf16(R"(D:\Literature_data\All_books)");

	// auto ls = recursive_lsdir(to_utf8(w));
	// std::cout << "Took lsdir!" << std::endl;

	const size_t size = fs_folder_total_size(w);

	hvn3::ByteSize sz(size);

	std::cout << sz << std::endl;
}

