//
// Created by Vova on 26.05.2020.
//

#pragma once

#include "pch.h"

#include "encoding/encoder.h"

/// Common:
template <class Func> std::string encoding_safe_apply(const std::string& string){
	encoding original_enc = recode::determine_encoding(string);

	std::wstring good_encoded;

	if (original_enc == encoding::any || original_enc == encoding::cp1251)
		good_encoded = recode::from_cp1251_to_utf16(string);

	else good_encoded = recode::from_utf8_to_utf16(string);

	std::wstring res = Func::do_work(good_encoded);

	if (original_enc == encoding::any || original_enc == encoding::cp1251) return recode::to_cp1251(res);
	else return recode::to_utf8(res);
}

/// To lower:
inline std::wstring to_lower(const std::wstring& string){
	std::wstring res = string;
	CharLowerW(res.data());

	return res;
}

struct to_lower_performer {
	static std::wstring do_work(const std::wstring& w)
	{ return to_lower(w); }
};

inline std::string to_lower(const std::string& string)  {
	return encoding_safe_apply<to_lower_performer>(string);
}

/// To upper:
inline std::wstring to_upper(const std::wstring& string){
	std::wstring res = string;
	CharUpperW(res.data());

	return res;
}

struct to_upper_performer {
	static std::wstring do_work(const std::wstring& w)
	{ return to_upper(w); }
};

inline std::string to_upper(const std::string& string)  {
	return encoding_safe_apply<to_upper_performer>(string);
}

/// Language recognition:
inline bool is_russian_letter(const char c) { // C is in cp1251!
	constexpr unsigned char russian_A = 192;
	constexpr unsigned char russian_a = 224;
	constexpr char russian_ch_A = char(russian_A);
	constexpr char russian_ch_a = char(russian_a);

	constexpr unsigned char russian_Ya = 223;
	constexpr unsigned char russian_ya = 255;
	constexpr char russian_ch_Ya = char(russian_Ya);
	constexpr char russian_ch_ya = char(russian_ya);

	constexpr unsigned char russian_Yo = 168;
	constexpr unsigned char russian_yo = 184;
	constexpr char russian_ch_Yo = char(russian_Yo);
	constexpr char russian_ch_yo = char(russian_yo);

	return (russian_ch_A <= c  && c <= russian_ch_Ya) || (russian_ch_a <= c  && c <= russian_ch_ya) || (c == russian_ch_Yo) || (c == russian_ch_yo);
}

inline bool is_english_letter(const char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool is_letter(const char c){
	return is_russian_letter(c) || is_english_letter(c);
}

inline bool is_digit(const char c){
	// return (c >= '1' && c <= '9') || c == '0';
	return (c >= '0' && c <= '9');
}

inline bool is_from_word(const char c){
	return is_digit(c) || is_letter(c) || c == '`' || c == '\'' || c == '-' || c == '_';
}

inline bool is_identifier_symbol(const char c) {
	return is_letter(c) || c == '_';
}

inline bool is_space (const char c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

