cmake_minimum_required(VERSION 3.16)

# Useful macros:

# ^^^ End useful macros

if (WIN32)
    message("Platform: Windows")

    # message(${CMAKE_CXX_COMPILER_ID})
    # if(MSVC)
    #    message("Compiler: MSVC")
    # else()
    #    message("WTF compiler isn't MSVC on Windows??")
    #endif()
endif()

if (UNIX)
    message("Platform: *nix")
    # message("Compiler: ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")

    set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
    set(CMAKE_C_COMPILER "/usr/bin/gcc-10")

    if(CMAKE_CXX_COMPILER_ STREQUAL "GNU")
        message("Compiler: GCC")
        message("I hope, the version is 10: otherwise it won't compile!")
    else()
        message("I hope, the compiler is GCC and its version is 10 (or higher?): otherwise it won't compile!")
    endif()
endif()


###########################################################################
project(pythonic)
set(CMAKE_CXX_STANDARD 20)

# Platform Specific stuff:
if (WIN32)

    set(platform_specific_source_files

            encoding/win32_examples/utf8_except.h
            encoding/win32_examples/utf8_utf16_conversion.h

            encoding/variations/windows/cp1251_utf8.cpp
            encoding/variations/windows/cp1251_utf8.h
            encoding/variations/windows/utf8_utf16.cpp
            encoding/variations/windows/utf8_utf16.h
            encoding/variations/windows/cp1251_utf16.cpp
            encoding/variations/windows/cp1251_utf16.h

            encoding/variations/windows/utils.h
            files/platform/windows/file_reader_windows.h
            files/platform/windows/file_reader_windows.cpp

            files/platform/windows/file_walker_windows.cpp
            files/platform/windows/file_walker_windows.h

            )
endif (WIN32)

if (UNIX)

    set(platform_specific_source_files

            # Encoding:
            encoding/variations/linux/linux_recoding_base.h

            encoding/variations/linux/cp1251_utf8.h
            encoding/variations/linux/cp1251_utf8.cpp

            encoding/variations/linux/utf8_utf32.h
            encoding/variations/linux/utf8_utf32.cpp

            encoding/variations/linux/cp1251_utf32.h
            encoding/variations/linux/cp1251_utf32.cpp

            encoding/variations/linux/utils.h

            # Files
            files/platform/linux/file_reader_linux.h
            files/platform/linux/file_reader_linux.cpp

            files/platform/linux/file_walker_linux.h
            files/platform/linux/file_walker_linux.cpp

            )

endif (UNIX)


include_directories(${CMAKE_CURRENT_LIST_DIR})

set(PYTHONIC_SOURCES pythonic.h

        maths/statistics.h
        maths/statistics.cpp

        encoding/encoder.cpp
        encoding/encoder.h

        other/typedefs.h

        maths/simple_functions.h


        encoding/encode_exception.cpp
        encoding/encode_exception.h


        displaying/print_stl.h

        displaying/byte_sizes/BitSize.cpp
        displaying/byte_sizes/BitSize.h
        displaying/byte_sizes/ByteSizeCommon.cpp
        displaying/byte_sizes/ByteSizeCommon.h
        displaying/byte_sizes/ByteSize.cpp
        displaying/byte_sizes/ByteSize.h

        displaying/colored_printing.h

        plotting/plotter.cpp
        plotting/plotter.h

        geometry/line.cpp
        geometry/line.h
        geometry/point.cpp
        geometry/point.h

        maths/numpyic.cpp
        maths/numpyic.h

        n_dim/nd_array.h

        smoothing/smoothing.cpp
        smoothing/smoothing.h
        smoothing/density_counter.cpp
        smoothing/density_counter.h
        other/python_builtins.cpp
        other/python_builtins.h
        other/letter_utils.h
        maths/randomizator.cpp
        maths/randomizator.h

        timing/Timer.cpp
        timing/Timer.h

        geometry/circle.cpp
        geometry/circle.h
        n_dim/nd_point.h
        displaying/type_printer.h
        other/Counter.h
        timing/delayed_launcher.h
        timing/task_scheduler.h
        n_dim/nd_array.inl.h
        timing/easy_measurer.h


        utils_constexpr/stringing.h



        files/file_reader_base.h
        files/file_reader.h

        files/file_walker_base.h
        files/file_walker.h


        tests/threading_tests/thread_distribution_test.h
        tests/threading_tests/thread_pool_test.h

        threading/thread_utils.h
        threading/thread_utils.cpp
        threading/static_thread_pool.cpp
        threading/static_thread_pool.h

        timing/multirun_timer.cpp timing/multirun_timer.h tests/timing_tests/multirun_timer_tests.h algorithms/binary_search.h algorithms/segment_tree.h displaying/printing_utils.h)

foreach(this_source_file ${platform_specific_source_files})
    list(APPEND PYTHONIC_SOURCES ${this_source_file})
endforeach()

# THE ACTUAL PYTHONIC:
add_library(pythonic ${PYTHONIC_SOURCES})



# Platform dependant libraries:
if(WIN32)
    # Pass
else()
    target_link_libraries(pythonic tbb pthread)
endif()




set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

# set(Json_DIR D:/lib/json)
find_package(Json REQUIRED)
include_directories(${Json_include_directories})

include(cotire)
cotire(pythonic)



## Project with tests:

project(pythonic_test)
set_target_properties(pythonic PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pythonic_pch.h")

include_directories(pythonic_test tests)



# Platform dependent tests:

set(platform_dependent_tests_linux

        tests/encoding_tests/linux_recode_test.h
        tests/linux_fs_tests.h

        )

set(platform_dependent_tests_windows

        tests/windows_fs_tests.h

        )

#############

set(pythonic_test_SOURCES

        main.cpp


        tests/encoding_tests/simple_encoding_tests.h

        tests/printing_tests.h

        tests/encoding_tests/file_reading_tests.h
        tests/encoding_tests/cp1251_tests.h

        tests/encoding_tests/auto_decode_tests.h
        tests/json_and_plot_test.h
        tests/smoothing_test.h
        tests/nd_test.h
        tests/python_test.h
        tests/random_tests.h
        tests/stl_tests.h
        tests/other_tests.h
        tests/timing_tests.h


        tests/geom_test.h
        tests/algorithm_tests/bs_tests.h tests/math_tests/averagers_tests.h)

#################

if (UNIX)
    set(platform_dependent_tests ${platform_dependent_tests_linux})
endif()

if (WIN32)
    set(platform_dependent_tests ${platform_dependent_tests_windows})
endif()

foreach(this_source_file ${platform_dependent_tests})
    list(APPEND pythonic_test_SOURCES ${this_source_file})
endforeach()

# Actual executable for pythonic:
add_executable(pythonic_test
        ${pythonic_test_SOURCES}
        )

target_link_libraries(pythonic_test pythonic)



# print_target_libraries(pythonic)
# print_target_libraries(pythonic_test)
