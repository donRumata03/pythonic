//
// Created by vova on 21.10.2020.
//


#pragma once

#include <pythonic.h>

inline void test_reading_cp1251_file() {
    std::string filename = (pythonic_base_dir / "tests/encoding_tests/test_files/Привет-cp1251.txt").string();
    auto file_contents = *read_file(filename);

    std::cout << file_contents << std::endl;
    std::cout << recode::to_utf8(file_contents) << std::endl;

}

