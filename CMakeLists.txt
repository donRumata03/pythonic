cmake_minimum_required(VERSION 3.16)

#####################################################################################
# Macro for precompiled headers:
MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
    IF(MSVC)
        GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
        SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
        SET(Sources ${${SourcesVar}})

        SET_SOURCE_FILES_PROPERTIES(
                ${PrecompiledSource}    PROPERTIES
                COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                OBJECT_OUTPUTS "${PrecompiledBinary}"
        )

        SET_SOURCE_FILES_PROPERTIES(
                ${Sources} PROPERTIES
                COMPILE_FLAGS "/Yu\"${PrecompiledBinary}\" /FI\"${PrecompiledBinary}\" /Fp\"${PrecompiledBinary}\""
                OBJECT_DEPENDS "${PrecompiledBinary}"
        )
    ENDIF(MSVC)

    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
ENDMACRO()
############################################################################################################


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




project(pythonic)

set(CMAKE_CXX_STANDARD 20)

include_directories(/)

set(PYTHONIC_SOURCES pythonic.h

        maths/statistics.h
        maths/statistics.cpp

        encoding/encoder.cpp
        encoding/encoder.h

        files/file_reader.cpp
        files/file_reader.h

        other/typedefs.h

        maths/simple_functions.h

        encoding/win32_examples/utf8_except.h
        encoding/win32_examples/utf8_utf16_conversion.h

        files/file_walker.cpp
        files/file_walker.h
        encoding/encode_exception.cpp
        encoding/encode_exception.h

        encoding/variations/cp1251_utf8.cpp
        encoding/variations/cp1251_utf8.h
        encoding/variations/utf8_utf16.cpp
        encoding/variations/utf8_utf16.h
        encoding/variations/cp1251_utf16.cpp
        encoding/variations/cp1251_utf16.h

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

        geometry/circle.cpp geometry/circle.h n_dim/nd_point.h displaying/type_printer.h other/Counter.h timing/delayed_launcher.h timing/task_scheduler.h)

# message("${PYTHONIC_SOURCES}")

# ADD_MSVC_PRECOMPILED_HEADER("pch.h" "pch.cpp" PYTHONIC_SOURCES)

add_library(pythonic
        ${PYTHONIC_SOURCES})


set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)

cotire(pythonic)

project(pythonic_test)
set_target_properties(pythonic PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.h")

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
        tests/json_and_plot_test.h tests/smoothing_test.h tests/nd_test.h tests/python_test.h tests/random_tests.h tests/stl_tests.h tests/other_tests.h tests/date_test.h)



target_link_libraries(pythonic_test pythonic)



print_target_libraries(pythonic)
print_target_libraries(pythonic_test)
