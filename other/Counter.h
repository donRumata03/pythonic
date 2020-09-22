//
// Created by Vova on 29.05.2020.
//

#pragma once

#include "pythonic_pch.h"

template <typename T> std::vector<T> local_unique_in_order(const std::vector<T>& iterable){
	std::vector<T> res;
	for(size_t pos = 0; pos < iterable.size(); pos++){
		if (pos == 0 || iterable[pos - 1] != iterable[pos]) res.push_back(iterable[pos]);
	}
	return res;
}

template <typename T> std::vector<T> unique_in_order(const std::vector<T>& iterable){
	std::vector<T> res;
	std::unordered_set<T> s;
	for(auto& elem : iterable){
		if (s.find(elem) != s.end()){

		}
		else {
			res.push_back(elem);
			s.insert(elem);
		}
	}
	return res;
}


template<class T, class E> std::vector<std::pair<T, E>> get_sorted_elements(const std::unordered_map<T, E>& m) {
	std::vector<std::pair<T, E>> res;
	for (auto& p : m) res.emplace_back(p);

	sort(res.begin(), res.end(), [](std::pair<T, E>& p, std::pair<T, E>& e) { return p.second > e.second; });
	return res;
}

template<class T, class E> std::vector<std::pair<T, E>> get_sorted_elements(const std::map<T, E>& m) {
	std::vector<std::pair<T, E>> res;
	for (auto& p : m) res.emplace_back(p);

	sort(res.begin(), res.end(), [](pair<T, E>& p, pair<T, E>& e) { return p.second > e.second; });

	return res;
}


template<class T> std::vector<std::pair<T, size_t>> get_sorted_elements(const std::vector<T>& elements) {
	std::unordered_map<T, size_t> res;

	for (auto& el : elements) ++res[el];
	return get_sorted_elements(res);
}

template<class T> std::unordered_map<T, size_t> make_Counter(const std::vector<T>& elements) {
	std::unordered_map<T, size_t> res;

	for (auto& el : elements) ++res[el];
	return res;
}

