//
// Created by vova on 13.10.2020.
//

#pragma once

#include "pythonic_pch.h"
#include "iconv.h"

template <class InputStringType, class OutputStringType, size_t in_to_out_string_size_increasing>
OutputStringType recode_base(const InputStringType& input_string, const char* from_code, const char* to_code) {
    iconv_t converter = iconv_open(to_code, from_code);

    char* pointer_to_input = input_string.data();
    size_t input_size = input_string.size();

    std::string res;
    res.resize(input_string.size() * in_to_out_string_size_increasing);
    char* pointer_to_write_output = res.data();
    size_t out_max_size = res.size();

    size_t code = iconv(converter, &pointer_to_input, &input_size, &pointer_to_write_output, &out_max_size);
    std::cout << "Res code is: " << code << std::endl;

    res.erase(res.begin() + res.find_first_of('\0'), res.end());
    res.shrink_to_fit();

    return res;
}
