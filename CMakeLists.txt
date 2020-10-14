cmake_minimum_required(VERSION 3.16)

if (WIN32)
    message("Platform: Windows")

    # message(${CMAKE_CXX_COMPILER_ID})
    #if(MSVC)
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


macro(print_target_libraries target_name)
    message(___________________________________________)
    get_target_property(OUT ${target_name} LINK_LIBRARIES)
    if (${OUT} STREQUAL OUT-NOTFOUND)
        message(No\ linked\ libraries\ found\ for\ project\ "${target_name}"\ :\()
    else()
        message(Here\ are\ the\ libraries\ linked\ to\ project\ "${target_name}":)
        message(STATUS ${OUT})

    endif()

message(___________________________________________)
endmacro()

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
            files/file_reader_windows.h
            files/file_reader_windows.cpp
            )
endif (WIN32)

if (UNIX)

    set(platform_specific_source_files

            encoding/variations/linux/linux_recoding_base.h

            encoding/variations/linux/cp1251_utf8.cpp
            encoding/variations/linux/cp1251_utf8.h
            encoding/variations/linux/utf8_utf16.cpp
            encoding/variations/linux/utf8_utf16.h
            encoding/variations/linux/cp1251_utf16.cpp
            encoding/variations/linux/cp1251_utf16.h

            encoding/variations/linux/utils.h

            files/file_reader_linux.cpp
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



        files/file_walker.cpp
        files/file_walker.h

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
        other/thread_utils.h

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

        files/file_reader_base.h

        utils_constexpr/stringing.h

        files/file_reader_linux.h files/file_reader.h)

foreach(this_source_file ${platform_specific_source_files})
    list(APPEND PYTHONIC_SOURCES ${this_source_file})
endforeach()

# message("${PYTHONIC_SOURCES}")
# ADD_MSVC_PRECOMPILED_HEADER("pch.h" "pch.cpp" PYTHONIC_SOURCES)

add_library(pythonic ${PYTHONIC_SOURCES})

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


add_executable(pythonic_test

        tests/main.cpp


        tests/encoding_tests/simple_encoding_tests.h

        tests/encoding_tests/fs_test.h
        tests/fs_tests.h
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


        tests/geom_test.h)



target_link_libraries(pythonic_test pythonic)



# print_target_libraries(pythonic)
# print_target_libraries(pythonic_test)
