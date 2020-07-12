//
// Created by Vova on 24.05.2020.
//


#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <encoding/encoder.h>

#include <filesystem>
namespace fs = std::filesystem;


std::vector<std::string> lsdir(const std::string& path); /// path is assumed to be encoded in utf-8; result is also utf-8

std::vector<std::string> recursive_lsdir(const std::string& path); /// path is assumed to be encoded in utf-8; result is also utf-8

size_t fs_file_size(const std::wstring& path);
inline size_t fs_file_size(const std::string& path) { return fs_file_size(recode::from_utf8_to_utf16(path)); } /// path is assumed to be encoded in utf-8!!!

size_t fs_folder_total_size(const std::wstring& path);
inline size_t fs_folder_total_size(const std::string& path) { return fs_folder_total_size(recode::from_utf8_to_utf16(path)); }
