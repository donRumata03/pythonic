//
// Created by vova on 21.10.2020.
//


#pragma once

#include "files/file_walker_base.h"

namespace file_walker_detail {
    template<given_filename_encoding given_encoding, class Functor>
    auto invoke_with_utf8(const std::string& path, const Functor& the_functor) {
        if constexpr (given_encoding == given_filename_encoding::utf8) {
            return the_functor(path);
        }
        else {
            return the_functor(recode::to_utf8(path));
        }
    }
}


template<given_filename_encoding given_encoding>
std::vector<std::string> lsdir(const std::string& path) {
    return file_walker_detail::invoke_with_utf8<given_encoding>(path, base_lsdir<std::string>);
}

template<given_filename_encoding given_encoding>
std::vector<std::string> recursive_lsdir(const std::string& path) {
    return file_walker_detail::invoke_with_utf8<given_encoding>(path, base_recursive_lsdir<std::string>);
}



template<given_filename_encoding given_encoding>
size_t fs_file_size(const std::string& path) {
    return file_walker_detail::invoke_with_utf8<given_encoding>(path, base_fs_file_size<std::string>);
}

template<given_filename_encoding given_encoding>
size_t fs_folder_total_size(const std::string& path) {
    return file_walker_detail::invoke_with_utf8<given_encoding>(path, base_fs_folder_total_size<std::string>);
}


