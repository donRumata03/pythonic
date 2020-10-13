if (DEFINED Json_DIR)
    set(Json_include_directories ${Json_DIR})
    message(STATUS "Package Json successfully found in specified directory: ${Json_include_directories}")
    return()
endif()


set (Json_possible_dirs
        "D:/Cpp_Libs/json"
        "D:/lib/json"
        "D:/libraries/json"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/json"
        "~/dev/lib/json"
)

set(Json_possible_locations)

set(found_in_default_dirs OFF)
set(json_location)

foreach(j_dir ${Json_possible_dirs})
    set(location ${j_dir}/json.hpp)
    list(APPEND Json_possible_locations ${location})

    if (EXISTS ${location})
        set(found_in_default_dirs ON)
        set(json_location ${location})
        set(json_directory ${j_dir})
    endif()

endforeach()



if (NOT found_in_default_dirs)
    message(FATAL_ERROR "Json_DIR isn`t specified, can`t also find in default locations (${Json_possible_locations})")
endif()


set(Json_include_directories ${json_directory})

message(STATUS "Package Json successfully found in default directory: ${Json_include_directories}")