//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <vector>
#include <optional>
#include <string>
#include <fstream>
#include <iostream>

std::optional<std::string> read_file(const std::wstring& filename);
std::optional<std::string> read_file(const std::string& utf8_filename); // Assume that the string is utf8 encoded!!!
void write_file(const std::string& data, const std::wstring& filename);

uint64_t file_length(const std::wstring& filename);

// std::optional<std::string> read_utf8_file_to_cp1251(const std::string& filename);

