//
// Created by Vova on 24.05.2020.
//

#pragma once

#include <vector>
#include <optional>
#include <string>
#include <fstream>
#include <iostream>

#include "file_reader_base.h"

// Special for Windows:
std::optional<std::string> read_file(const std::wstring& filename);
void write_file(const std::string& data, const std::wstring& filename);
uint64_t file_size_in_bytes(const std::wstring& filename);

