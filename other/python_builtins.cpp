//
// Created by Vova on 26.05.2020.
//

#include "python_builtins.h"

std::vector<std::string> split_words(const std::string &s)
{
	auto spl = split_if(s, [](char c) {return !is_from_word(c); });
	std::vector<std::string> res;
	res.reserve(spl.size());
	for (auto& ss : spl) if (ss != "-") res.emplace_back(ss);
	return res;
}

std::vector<std::string> split_lines(const std::string & s) {
	auto res = split(s, { '\n' });
	for (auto& el : res)
	{
		if (!el.empty() && el[el.size() - 1] == '\r')
		{
			el = Slice(el, noslice, el.size() - 1);
		}
	}
	return res;
}

std::vector<std::string> split_sentences(const std::string &s)
{
	return split(s, { '.', '?', '!', '\n' });
}

std::vector<std::string> split(const std::string &s, const std::vector<char> &split_by)
{
	return split_if(s, [&](const char c) { return is_in(c, split_by); });
}

std::vector<std::pair<double, double>> zip(const std::vector<double> &vec1, const std::vector<double> &vec2)
{
	assert(vec1.size() == vec2.size());
	std::vector<std::pair<double, double>> res(vec1.size());
	for (size_t i = 0; i < vec1.size(); i++) res[i] = { vec1[i], vec2[i] };

	return res;
}

std::pair<std::vector<double>, std::vector<double>> unzip(const std::vector<std::pair<double, double>> &pair_vector)
{
	std::pair<std::vector<double>, std::vector<double>> res;
	res.first.reserve(pair_vector.size());
	res.second.reserve(pair_vector.size());

	for(auto& p : pair_vector) {
		res.first.emplace_back(p.first);
		res.second.emplace_back(p.second);
	}
	return res;
}
