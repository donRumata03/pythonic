//
// Created by vova on 14.10.2020.
//

#pragma once

#include "pythonic_pch.h"
#include ""


template<class FileSystemStringType>
std::optional<std::string> read_file(const FileSystemStringType &filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);

    if (in)
    {
        std::string contents;

        in.seekg(0, std::ios::end);
        contents.resize(static_cast<const unsigned int>(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }

    std::string utf_recoded_filename;
    if constexpr (std::is_same_v<std::string, FileSystemStringType>) {
        // Linux => already in utf8
        utf_recoded_filename = filename;
    }
    else {
        utf_recoded_filename = recode::fr
    }
    std::cerr << "Failed to read file \"" << recode::to_utf8(filename) << "\": The file probably doesn`t exist!";

    return {};
}
