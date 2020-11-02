//
// Created by vova on 21.10.2020.
//


#pragma once

#include <pythonic.h>

inline void test_reading_cp1251_file() {
    std::string filename = (pythonic_base_dir / "tests" / "encoding_tests" / "test_files" / "Привет-cp1251.txt").string();
    auto file_contents = *read_file<given_filename_encoding::utf8>(filename);

    std::cout << file_contents << std::endl;
    std::cout << recode::to_utf8(file_contents) << std::endl;

}


inline void cp1251_forward_and_back_converting_tests() {
    std::cout << "Forward: " << std::endl;

    // std::string initial_string = "Привет, world!";
    std::string initial_string = "Привет";

    std::string cp1251_string = recode::to_cp1251(initial_string);
    std::cout << "CP2151 string: " << cp1251_string;

    std::string utf8_string = recode::to_utf8(cp1251_string);
    std::cout << "UTF8 string: " << utf8_string;
}

inline void utf32_forward_and_back_converting_tests() {
    std::cout << "Forward: " << std::endl;

    // std::string initial_string = "Привет, world!";
    std::string initial_string = "Привет";

    std::wstring utf32_string = recode::from_utf8_to_utf32(initial_string);
    // std::cout << "utf32 string: " << utf32_string;

    std::string utf8_string = recode::to_utf8(utf32_string);
    std::cout << "UTF8 string: " << utf8_string;
}


inline void cp1251_utf32_forward_and_back_converting_tests() {
    std::cout << "Forward: " << std::endl;

    // std::string initial_string = "Привет, world!";
    std::string initial_string = "Привет";

    std::wstring utf32_string = recode::from_utf8_to_utf32(initial_string);
    // std::cout << "utf32 string: " << utf32_string;

    auto cp1251_string = recode::to_cp1251(utf32_string);
    auto second_utf32_string = recode::from_cp1251_to_utf32(cp1251_string);

    std::string utf8_string = recode::to_utf8(utf32_string);
    std::cout << "UTF8 string: " << utf8_string;
}