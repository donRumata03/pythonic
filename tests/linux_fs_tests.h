//
// Created by vova on 23.10.2020.
//


#pragma once

#include <pythonic.h>


inline void test_lsdir() {
    std::cout << lsdir<given_filename_encoding::utf8>(
            (pythonic_base_dir).string()
            ) << std::endl;
}


inline void test_recursive_lsdir() {
    std::cout << recursive_lsdir<given_filename_encoding::utf8>(
            (pythonic_base_dir).string()
    ) << std::endl;
}

inline void test_fs_file_size() {
    auto filename = (pythonic_base_dir / "tests" / "encoding_tests" / "test_files" / "Привет-cp1251.txt").string();

    std::cout << "File size: " << fs_file_size<given_filename_encoding::utf8>(
        filename
    ) << std::endl;

    std::cout << "File contents: " << recode::to_utf8(*read_file<given_filename_encoding::utf8>(filename)) << std::endl;
}

inline void test_total_folder_size() {
    std::cout << ByteSize(fs_folder_total_size<given_filename_encoding::utf8>(
            (pythonic_base_dir).string()
    ), BytePrefix::Binary) << std::endl;
}

