//
// Created by Vova on 26.05.2020.
//

#pragma once
#include "pythonic_pch.h"

#include "letter_utils.h"

/// In / Is_in
template<class T> bool in(const std::set<T>& s, const T& el)
{
	return s.find(el) != s.end();
}
template<class T> bool in(const std::unordered_set<T>& s, const T& el)
{
	return s.find(el) != s.end();
}
template<class T, class E> bool in(const std::unordered_map<T, E>& m, const  T& el)
{
	return m.find(el) != m.end();
}
template<class T, class E> bool in(const std::map<T, E>& m, const T& el)
{
	return m.find(el) != m.end();
}

template<class T, class E> bool is_in(const T& target, E&& container) {
	for (auto &val : container) {
		if (val == target) {
			return true;
		}
	}
	return false;
}


/// Join:
template<class T>
std::string join(const std::string& splitter, const T& container) {
	std::string res;

	int counter = 0;
	for (const auto &i : container)
	{
		res += std::to_string(i);
		if (counter != container.size() - 1) res += splitter;
		counter++;
	}
	return res;
}

/// Slice:
inline constexpr size_t noslice = std::string::npos;
template<class T> T Slice(const T& container, size_t idx_beg = noslice, size_t idx_end = noslice, size_t step = noslice) {
	if (idx_beg == noslice) idx_beg = 0;
	if (idx_end == noslice) idx_end = container.size();
	if (step == noslice) step = 1;
	T result;
	for (size_t idx = idx_beg; idx < idx_end; idx += step) {
		result.push_back(container[idx]);
	}
	return result;
}

///  Cut:
template <class Container, class Pred> Container cut_if(const Container& container, Pred predicate) {
	if (container.empty()) return container;

	size_t first_index = 0;
	for(; first_index < container.size(); first_index++){
		if (!predicate(container[first_index])) {
			break;
		}
	}

	size_t last_index = container.size() - 1;

	for(; last_index >= first_index; last_index--){
		if (!predicate(container[last_index])){
			last_index++;
			break;
		}
	}

	return Slice(container, first_index, last_index);
}

inline std::string cut_symbols(const std::string& s, std::vector<char>&& symbols)
{
	return cut_if(s, [&](char ch) -> bool { return is_in(ch, symbols); });

	/*

	std::string pre_res;
	bool flag1 = false;
	for(auto c : s) {
		if (!is_in(c, symbols)) flag1 = true;
		if (flag1) pre_res.push_back(c);
	}
	std::string res;
	bool flag2 = false;
	for(auto index = static_cast<long long>(pre_res.size() - 1); index >= 0; index--) {
		if (!is_in(pre_res[index], symbols)) flag2 = true;
		if (flag2) res.push_back(pre_res[index]);
	}
	reverse(res.begin(), res.end());
	return res;

	*/
}

inline std::string cut_spaces(const std::string& s)
{
	return cut_symbols(s, { ' ', '\n', '\t', '\r'});
}

inline std::string cut_not_from_word(const std::string& s)
{
	return cut_if(s, [](char c){ return !is_from_word(c); });
}



/// Splitting:
template<class T> std::vector<std::string> split_if(const std::string& s, T predicate){
	std::vector<std::string> result;
	size_t last_word_beg = 0;
	bool in_word = false;
	size_t index = 0, len = s.length();
	size_t this_length;
	for (char c : s) {
		// std::cout << recode::to_utf8(std::string{c}) << " : " << std::boolalpha << predicate(c) << std::endl;
		if (predicate(c)) { // Word splitter detected!
			if (in_word) { // end word
				/*
				in_word = false;
				this_length = index - last_word_beg;
				std::string this_word;
				this_word.reserve(this_length + 1);
				for (size_t i = last_word_beg; i < index; i++) {
					this_word.push_back(s[i]);
				}
				result.push_back(this_word);
				 */

				in_word = false;
				this_length = index - last_word_beg;

				auto& this_string = result.emplace_back();
				this_string.resize(this_length);
				std::copy(s.begin() + last_word_beg, s.begin() + index, this_string.begin());
			}
			else { // Still rubbish

			}
		}
		else { // Non word_splitter (letter)
			if (in_word) { // In word => continue cheeling

			}
			else { // Letter => word beginning
				last_word_beg = index;
				in_word = true;
			}
		}
		index++;
	}

	if (!s.empty() && !predicate(s[s.size() - 1])) { // // add last word
		this_length = index - last_word_beg;
		std::string this_word;
		this_word.reserve(this_length);
		for (size_t i = last_word_beg; i < len; i++) {
			this_word.push_back(s[i]);
		}
		result.push_back(this_word);
	}
	if (!result.empty())	return result;
	return {};
} // Predicate function says, when the char should be ignored


std::vector<std::string> split(const std::string& s, const std::vector<char>& split_by = { ' ', '\n', '\t', '\r' });
std::vector<std::string> split_sentences(const std::string& s);
std::vector<std::string> split_lines(const std::string& s);
std::vector<std::string> split_words(const std::string& s);

/// Cut:
template<class T, class E, class C> auto cut(T val, E _min, C _max)/* -> decltype(val + _min + _max) */ {
	if (val < _min) return static_cast<decltype(val + _min + _max)>(_min);
	if (val > _max) return static_cast<decltype(val + _min + _max)>(_max);
	return static_cast<decltype(val + _min + _max)>(val);
}

/// Print percent:
template<class T, class E> void print_percent(T part, E all_amount, std::ostream& out = std::cout) {
	out << part << " / " << all_amount << " ( " << 100. * part / all_amount << "% )";
}

template <class T, class E> struct percent_plotter {
	T part;
	E all_amount;
	percent_plotter(T arg1, E arg2) : part(arg1), all_amount(arg2) {}
};

template <class T, class E> std::ostream& operator<< (std::ostream& out, const percent_plotter<T, E>& plotter) {
	print_percent(plotter.part, plotter.all_amount, out);
	return out;
}

/// Zip:
std::vector<std::pair<double, double>> zip(const std::vector<double> &vec1, const std::vector<double> &vec2);
std::pair<std::vector<double>, std::vector<double>> unzip(const std::vector<std::pair<double, double>>& pair_vector);



/// Copy_to: moves all elements of the given container to the container of type given as Template parameter:

/**
 *
 * @usage:
 * @code
 * std::vector<double> values = { 1., 4.6, 7, 34.65 };
 * auto new_set = copy_to<std::unordered_set<double>>(values);
 * @endcode
 */
template<class Output_container_t, class Input_container_t>
typename std::enable_if<std::is_same<typename Output_container_t::value_type, typename Input_container_t::value_type>::value, Output_container_t>::type
        copy_to (Input_container_t& input_container) {
	using T = Input_container_t::value_type;

	// std::remove_const_t<Output_container_t> res(input_container.size());
	Output_container_t res(input_container.begin(), input_container.end());

	// std::copy(input_container.begin(), input_container.end(), std::begin(res));

	std::cout << type_name<decltype(res)>() << std::endl;

	/*for () {

	}*/

	return res;
}
