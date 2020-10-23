//
// Created by Vova on 26.05.2020.
//

#pragma once

#include <pythonic.h>

inline void test_enc_detecting(){
	std::string base_path = R"(D:\Projects\Tests\enc_test\recognize_testing)";
	auto files = lsdir<given_filename_encoding::cp1251>(base_path);

	for(auto& file : files){
		std::cout << file << " : " << recode::determine_encoding(*read_file(file)) << std::endl;
	}
}

inline void auto_recode_test(){
	std::string base_path = R"(D:\Projects\Tests\enc_test\recognize_testing)";
	auto files = lsdir<given_filename_encoding::cp1251>(base_path);

	for(auto& file : files){
		std::cout << file << " : " << recode::auto_recode(*read_file(file), encoding::utf8) << std::endl;
	}
}

inline void auto_lower_upper_test(){
	std::wstring w = recode::from_utf8_to_utf16("ПрИвет!");
	std::cout << recode::to_utf8(to_lower(w)) << std::endl;

	std::cout << recode::to_utf8(to_lower(recode::to_cp1251("Привет, Hello!"))) << std::endl;
	std::cout << recode::to_utf8(to_upper(recode::to_cp1251("привет, Hello!"))) << std::endl;
	std::cout << to_upper("привет, Hello!") << std::endl;
}


