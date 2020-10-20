//
// Created by Vova on 25.05.2020.
//

#pragma once


#include <iostream>
#include <vector>
#include <map>
#include <set>

#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <type_traits>

#include "encoding/encoder.h"

// Declarations:

template <class T> void print(const T &something, std::ostream &out = std::cout) noexcept;

template <class Ch> void print(const std::basic_string<Ch>& string, std::ostream& out = std::cout) noexcept;
void print(const std::wstring& string, std::wostream& out = std::wcout) noexcept;
void print(const std::wstring& string, std::ostream& out = std::cout) noexcept;

template<class T> void print(const std::vector<T>& vec, std::ostream& out = std::cout) noexcept;

template<class T, class E> void print(const std::map<T, E>& map, std::ostream& out = std::cout) noexcept;
template<class T, class E> void print(const std::unordered_map<T, E>& map, std::ostream& out = std::cout) noexcept;

template<class T> void print(const std::set<T>& set, std::ostream& out = std::cout) noexcept;
template<class T> void print(const std::unordered_set<T>& set, std::ostream& out = std::cout) noexcept;

template<class T, class E> void print(const std::pair<T, E>& p, std::ostream& out = std::cout) noexcept;
template<class ... Args> void print(const std::tuple<Args...>& tuple, std::ostream& out = std::cout) noexcept;

template <class T, class E, class... Args> void print(T arg1, E arg2, Args... args, std::ostream& out = std::cout);


// Definitions:

template<class T> void print(const std::vector<T>& vec, std::ostream& out) noexcept {
	out << "[";
	size_t i = 0;
	for (auto& el : vec) {
		print(el, out);

		if (i != vec.size() - 1) out << ", ";
		i++;
	}
	out << "]";
}

template <class T> void print(const std::set<T> & set, std::ostream & out) noexcept
{
	out << "{ ";
	size_t counter = 0;
	for (auto& val : set) {

		print(val, out);

		if (counter != set.size() - 1) out << ", ";
		counter++;
	}
	out << " }";
}
template <class T> void print(const std::unordered_set<T>& set, std::ostream& out) noexcept
{
	std::set<T> to_print;
	auto it = set.begin();
	while (it != set.end()) {
		to_print.insert(*it); it++;
	}
	print(to_print);
}

template<class T, class E> void print(const std::map<T, E>& map, std::ostream& out) noexcept {
	if (map.empty()) {
		out << "{}\n";
		return;
	}
	out << "{\n";
	size_t counter = 0;
	for (auto& p : map) {
		out << "\t";

		print(p.first, out);

		out << " : ";

		print(p.second, out);

		if (counter != map.size() - 1) { out << ','; }
		out << "\n";
		// if (counter != map.size() - 1) { out << '\n'; }
		counter++;
	}
	out << "}";
}
template<class T, class E> void print(const std::unordered_map<T, E>& map, std::ostream& out) noexcept {
	std::map<T, E> to_print;
	auto it = map.begin();
	while (it != map.end()) {
		to_print.insert(*it); it++;
	}
	print(to_print, out);
}


template <class Ch> void print(const std::basic_string<Ch>& string, std::ostream &out) noexcept
{
	out << "\"" << string << "\"";
}
inline void print(const std::wstring &string, std::wostream &out) noexcept
{
	out << L"\"" << string << L"\"";
}
inline void print(const std::wstring &string, std::ostream &out) noexcept
{
	out << "\"" << recode::to_utf8(string) << "\"";
}

template<class T, class E> void print (const std::pair<T, E>& p, std::ostream& out) noexcept {
	out << "(";
	print(p.first, out);
	print(", ", out);
	print(p.second, out);
	out << ")";
}

template<class T> void print(const T &something, std::ostream &out) noexcept
{
	out << something;
}


namespace print_stl_impl
{
	template<typename Type, unsigned N, unsigned Last>
	struct tuple_printer
	{

		static void m_print(std::ostream &out, const Type &value)
		{
			// out << std::get<N>(value) << ", ";
			print(std::get<N>(value), out);
			out << ", ";
			tuple_printer<Type, N + 1, Last>::m_print(out, value);
		}
	};

	template<typename Type, unsigned N>
	struct tuple_printer<Type, N, N>
	{

		static void m_print(std::ostream &out, const Type &value)
		{
			// out << std::get<N>(value);
			print(std::get<N>(value), out);
		}

	};
}


template<class... Args>
void print(const std::tuple<Args...> &tuple, std::ostream &out) noexcept
{
	out << "(";
    print_stl_impl::tuple_printer<std::tuple<Args...>, 0, sizeof...(Args) - 1>::m_print(out, tuple);
 	out << ")";
}

// Function with multiple arguments:

template<class T, class E, class... Args>
void print(T arg1, E arg2, Args... args, std::ostream &out)
{
	// TODO!

	print(arg1, out);
	out << " ";
	print(arg2, out);
	out << " ";
	print(args..., out);
}



// Is printable determinator:
namespace is_printable_by_me_impl {
	template <typename T>       struct is_stl_container :std::false_type {};
	template <typename... Args> struct is_stl_container<			std::vector            <Args...>>			:std::true_type {};

	template <typename... Args> struct is_stl_container<			std::unordered_set     <Args...>>			:std::true_type {};
	template <typename... Args> struct is_stl_container<			std::set               <Args...>>			:std::true_type {};

	template <typename... Args> struct is_stl_container<			std::unordered_map     <Args...>>			:std::true_type {};
	template <typename... Args> struct is_stl_container<			std::map               <Args...>>			:std::true_type {};

	template <typename... Args> struct is_stl_container<			std::tuple               <Args...>>			:std::true_type {};
	template <typename T, typename E> struct is_stl_container<		std::pair				<T, E>>				:std::true_type {};
	// template <typename T, std::size_t N> struct is_stl_container<	std::array				<T, N>>				:std::true_type {};

}

//type trait to utilize the implementation type traits as well as decay the type
template <typename T> struct is_printable_by_me {
	static constexpr bool value = is_printable_by_me_impl::is_stl_container<std::decay_t<T>>::value;
};

//  The actual operator:
template<class T> typename std::enable_if<is_printable_by_me<const T>::value, std::ostream&>::type operator << (std::ostream& out, const T& val)
{
	print(val, out);
	return out;
}


#define varname(var_name) #var_name << ": "<< var_name
#define printvar(some_variable) std::cout << varname(some_variable) << std::endl

