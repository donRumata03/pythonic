//
// Created by Vova on 24.05.2020.
//

#include <cassert>
#include "file_walker.h"
#include "encoding/encoder.h"

std::vector<std::string> lsdir(const std::string &path)
{
	std::wstring utf16_path = recode::from_utf8_to_utf16(path);
	fs::path system_path(utf16_path);

	auto it = fs::directory_iterator(system_path);

	std::vector<std::string> res;
	for(const auto& entry : it) {
		const fs::path& this_path = entry.path();
		std::wstring this_utf16_path = this_path.generic_wstring();
		res.push_back(recode::to_utf8(this_utf16_path));
	}

	return res;
}

std::vector<std::string> recursive_lsdir(const std::string &path)
{
	std::wstring utf16_path = recode::from_utf8_to_utf16(path);
	fs::path system_path(utf16_path);

	auto it = fs::recursive_directory_iterator(system_path);


	std::vector<std::string> res;
	for(const auto& entry : it) {
		const fs::path& this_path = entry.path();
		std::wstring this_utf16_path = this_path.generic_wstring();

		// std::cout << recode::to_utf8(this_utf16_path) << std::endl;

		res.push_back(recode::to_utf8(this_utf16_path));
	}

	return res;
}

size_t fs_file_size(const std::wstring &path)
{
	fs::path real_path{path};
	return fs::file_size(real_path);
}

size_t fs_folder_total_size(const std::wstring &path)
{
	// std::cout << "Counting folder size: " << recode::to_utf8(path) << std::endl;

	fs::path p {path};
	assert(fs::exists(p));
	assert(fs::is_directory(p));

	auto it = fs::recursive_directory_iterator(p);
	size_t size_counter = 0;


	// std::cout << "Got it!" << std::endl;

	for(const auto& entry : it) {
		const fs::path& this_path = entry.path();
		// std::wstring this_utf16_path = this_path.generic_wstring();
		if (entry.is_regular_file()) size_counter += entry.file_size();

		// std::cout << recode::to_utf8(this_utf16_path) << std::endl;
		// std::cout << size_counter << std::endl;
	}

	return size_counter;
}
