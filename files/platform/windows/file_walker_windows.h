//
// Created by vova on 21.10.2020.
//


#pragma once

#include "files/file_walker_base.h"

/// FS functions in platform native encoding:

inline std::vector<std::wstring> UCS2_lsdir(const std::wstring& path) {
	return base_lsdir(path);
}

inline std::vector<std::wstring> UCS2_recursive_lsdir(const std::wstring& path) {
	return base_recursive_lsdir(path);
}


inline size_t UCS2_fs_file_size(const std::wstring& path) {
	return base_fs_file_size(path);
}

inline size_t UCS2_fs_folder_total_size(const std::wstring& path) {
	return base_fs_folder_total_size(path);
}

/// Helper:
namespace file_walker_detail {
	template<given_filename_encoding given_encoding, class Functor>
	auto invoke_with_wstring(const std::string& path, const Functor& the_functor) {
		if constexpr (given_encoding == given_filename_encoding::utf8) {
			return the_functor(recode::from_utf8_to_utf16(path));
		}
		else {
			return the_functor(recode::from_utf8_to_utf16(path));
		}
	}

	template<given_filename_encoding target_encoding, class Functor, class ... Args>
	std::vector<std::string> recode_vector_result_back_from_wstring(const Functor& the_functor, const Args& ... args) {
		auto not_encoded_res = the_functor(args...);
		std::vector<std::string> res; res.reserve(not_encoded_res.size());

		for (auto& str : not_encoded_res) {
			if constexpr (target_encoding == given_filename_encoding::utf8) {
				res.push_back(recode::to_utf8(str));
			}
			else {
				res.push_back(recode::to_cp1251(str));
			}
		}

		return res;
	}
}


/// Required template implementations:

template<given_filename_encoding given_encoding>
std::vector<std::string> lsdir(const std::string& path) {
	return file_walker_detail::recode_vector_result_back_from_wstring<given_encoding>(
			file_walker_detail::invoke_with_wstring<given_encoding, decltype(UCS2_lsdir)>, path, UCS2_lsdir
	);
}

template<given_filename_encoding given_encoding>
std::vector<std::string> recursive_lsdir(const std::string& path) {
	return file_walker_detail::recode_vector_result_back_from_wstring<given_encoding>(
			file_walker_detail::invoke_with_wstring<given_encoding, decltype(UCS2_recursive_lsdir)>, path, UCS2_recursive_lsdir
	);
}


template<given_filename_encoding given_encoding>
size_t fs_file_size(const std::string& path) {
	return file_walker_detail::invoke_with_wstring<given_encoding>(path, UCS2_fs_file_size);
}

template<given_filename_encoding given_encoding>
size_t fs_folder_total_size(const std::string& path) {
	return file_walker_detail::invoke_with_wstring<given_encoding>(path, UCS2_fs_folder_total_size);
}


