#include <pythonic.h>
#include <tests/encoding_tests/auto_decode_tests.h>

#include "encoding_tests/file_reading_tests.h"
#include "encoding_tests/simple_encoding_tests.h"
#include "encoding_tests/fs_test.h"
#include "encoding_tests/cp1251_tests.h"

#include "fs_tests.h"
#include "printing_tests.h"
#include "python_test.h"
#include "nd_test.h"

#include "random_tests.h"
#include "stl_tests.h"
#include "other_tests.h"
#include "timing_tests.h"
#include "geom_test.h"

#include "tests/threading_tests/thread_distribution_test.h"

#include <json_and_plot_test.h>

#include <execution>


int main()
{
	// SetConsoleOutputCP(CP_UTF8);
	// SetConsoleCP(CP_UTF8);

	// system("chcp 65001");
    set_utf8_in_console();
    std::cout << pythonic_base_dir << std::endl;

	/// Encoding

	// test_utf16_files();
	// test_utf8_utf16_english_converting();
	// test_utf8_utf16_russian_file_writing();
	// test_reading_file_with_russian_name();
	// test_cp1251_file_writing();
	// test_cp1251_file_reading();
	// test_converting_bad_unicode_characters_to_cp1251();
	// test_enc_detecting();
	// auto_recode_test();
	// auto_lower_upper_test();
	// lang_recognition_test();


	/// Filesystem

	// test_path_joining();
	// test_file_size();
	// test_from_fs_path_reading();
	// test_folder_size();
	// test_lsdir();
	// test_fs_current_path();
	// test_file_reading();


	/// Printing

	// test_colored_printing();
	// test_automatic_colored_printing();
	// print_vector_test();
	// print_set_test();
	// print_map_test();
	// print_seq_test();
	// print_tuple_test();
	// print_stl_operator_test();
	// print_mul_args_test();
	// byte_printing_test();


	/// Json + plotting

	// simple_test_json();
	// basic_plot_test();
	// line_plot_test();
	// throwing_function_plotting_test();
	// throwing_everywhere_function_test();



	/// Python:
	// test_splitting();
	// circle_test();
	// test_point_index_operator();
	// point_operator_test ();
	// point_scaling_test();
	// test_almost_equal();
	// cut_tests();
	// test_mult();


	/// ND:
	// nd_point_test();
	// nd_indexing_test();
	// nd_get_points_test();
	// print_nd_array_test();
	// nd_slicing_test();
	// nd_for_eaches_test();
	// test_nd_array_sum();

	/// Smoothing
	// test_smoothing();


	/// Different

	// test_probability_choice();
	// test_random();
	// test_parallel_for_each();
	// test_copying_to();
	// test_point_comparison();

	/// Timing
	// test_delayed_launch();
	// test_task_scheduler();
	// date_test();
	// easy_measure_test();

	/// Threading:
	test_thread_distribution();


	return 0;
}
