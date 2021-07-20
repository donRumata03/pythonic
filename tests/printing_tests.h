//
// Created by Vova on 25.05.2020.
//

#pragma once

#include <pythonic.h>
#include <iostream>

inline void byte_printing_test(){
	hvn3::ByteSize bs(1024);
	std::cout << bs.Bits() << std::endl; // outputs 8192
	std::cout << bs.Bytes() << std::endl; // outputs 1024
	std::cout << bs.Kilobytes() << std::endl; // outputs 1
	std::cout << bs << std::endl; // outputs 1.00 KiB
}

inline void test_colored_printing() {
	colored_print("Hello, yellow world!", console_colors::yellow, console_colors::bold, console_colors::underlined);
}

inline void test_automatic_colored_printing() {
	std::cout << console_colors::red << console_colors::bold << console_colors::underlined << "Hello, red world!" << console_colors::remove_all_colors <<
	" Not red already, though..."
	<< color_ending_string << color_ending_string << color_ending_string << color_ending_string << color_ending_string << color_ending_string << color_ending_string << color_ending_string << color_ending_string
	<< console_colors::red << "Red!" << std::endl;
}

inline void print_vector_test(){
	std::vector<int> int_v = {
			42,
			239
	};
	print(int_v);

	std::vector<std::string> str_v = {
			"Hello!",
			"Привет!"
	};

	print(str_v);
}


inline void print_set_test(){
	std::unordered_set<int> int_v = {
			42,
			239
	};
	print(int_v);

	std::unordered_set<std::string> str_v = {
			"Hello!",
			"Привет!"
	};

	print(str_v);
}

inline void print_map_test(){
	std::unordered_map<int, std::string> int_v = {
			{       42, "No"            },
			{       239, "Yes"          }
	};
	print(int_v);

	std::unordered_map<std::string, int> str_v = {
			{"Hello!", 1},
			{"Привет!", 199}
	};

	print(str_v);
}

inline void print_seq_test()
{
	// print_sequence(std::integer_sequence<int, 20, 989, 89>{});
}

inline void print_tuple_test(){
	std::tuple<double, int, std::string> t = { 1., 42, "Hello!" };
	print(t);

	std::tuple<std::string, std::string, std::string> t2 = { "1.", "42", "Hello!" };
	print(t2, std::cout);

	// std::cout << t << std::endl;
}

inline void print_stl_operator_test(){
	std::tuple<double, int, std::string> t = { 1., 42, "Hello!" };
	std::cout << t << std::endl;

	std::vector<double> vec = { 1, 53, 232.232 };
	std::cout << vec << std::endl;

	std::string s = "Hello!";
	std::cout << s << std::endl;

	std::unordered_map<std::string, std::vector<std::tuple<double, std::string, size_t>>> scary_val = {
			{ "First", { {1.1, "Hello1", 42}, {3, "Hello2", 239} } },
			{ "Second", { {1.1, "Hello3!", 4242}, {3, "Hello4!", 2310} } }
	};

	std::cout << scary_val << std::endl;


	std::unordered_map<std::string, std::map<size_t, std::vector<std::string>>> mama = {
			{"Hey!", {{9, {"Big"}}}}
	};

	std::cout << mama << std::endl; // <- issue!
}

inline void print_mul_args_test(){
	// print(10, "100", std::cout);
}

inline void strikethrough_test() {
	std::cout << strike_text_through("Striken") << " string" << std::endl;
}




