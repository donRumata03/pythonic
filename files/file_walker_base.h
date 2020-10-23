//
// Created by vova on 21.10.2020.
//


#pragma once

#include "file_reader.h"


/// Declare templates:
template<class FileSystemStringType>
std::vector<FileSystemStringType> base_lsdir(const FileSystemStringType& path); /// path is assumed to be encoded in utf-8; result is also utf-8

template<class FileSystemStringType>
std::vector<FileSystemStringType> base_recursive_lsdir(const FileSystemStringType& path); /// path is assumed to be encoded in utf-8; result is also utf-8

template<class FileSystemStringType>
size_t base_fs_file_size(const FileSystemStringType& path);

template<class FileSystemStringType>
size_t base_fs_folder_total_size(const FileSystemStringType& path);


/// Declare functions to implement for each platform:

template<given_filename_encoding given_encoding>
std::vector<std::string> lsdir(const std::string& path);

template<given_filename_encoding given_encoding>
std::vector<std::string> recursive_lsdir(const std::string& path);


template<given_filename_encoding given_encoding>
size_t fs_file_size(const std::string& path);

template<given_filename_encoding given_encoding>
size_t fs_folder_total_size(const std::string& path);



/// Implement template functions:


template<class FileSystemStringType>
std::vector<FileSystemStringType> base_lsdir(const FileSystemStringType &path) {
    fs::path system_path(path);

    auto it = fs::directory_iterator(system_path);

    std::vector<FileSystemStringType> res;
    for(const auto& entry : it) {
        const fs::path& this_path = entry.path();
        FileSystemStringType native_string_path = this_path.native();
        res.push_back(native_string_path);
    }

    return res;
}


template<class FileSystemStringType>
std::vector<FileSystemStringType> base_recursive_lsdir(const FileSystemStringType &path) {
    fs::path system_path(path);

    auto it = fs::recursive_directory_iterator(system_path);

    std::vector<FileSystemStringType> res;
    for(const auto& entry : it) {
        const fs::path& this_path = entry.path();
        FileSystemStringType native_string_path = this_path.native();

        res.push_back(native_string_path);
    }

    return res;
}


template<class FileSystemStringType>
size_t base_fs_file_size(const FileSystemStringType &path) {
    fs::path system_path{path};
    return fs::file_size(system_path);
}

template<class FileSystemStringType>
size_t base_fs_folder_total_size(const FileSystemStringType &path) {
    fs::path system_path {path};
    if(!fs::exists(system_path)) throw std::runtime_error("The path should exist");
    if (!fs::is_directory(system_path)) throw std::domain_error("The path should be a folder");

    auto it = fs::recursive_directory_iterator(system_path);
    size_t size_counter = 0;

    for(const auto& entry : it) {
        const fs::path& this_path = entry.path();
        if (entry.is_regular_file()) size_counter += entry.file_size();
    }

    return size_counter;
}




