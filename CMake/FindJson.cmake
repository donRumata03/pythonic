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
)

set(
        Json_possible_rel_dirs

        "dev/lib/json"
        "lib/json"
)

set(Json_possible_locations)

set(found_in_default_dirs OFF)
set(json_location)


foreach(j_dir ${Json_possible_dirs})
    set(location "${j_dir}/json.hpp")
    list(APPEND Json_possible_locations ${location})

    # message(${location})


    if (EXISTS ${location})
        set(found_in_default_dirs ON)
        set(json_location ${location})
        set(json_directory ${j_dir})
    endif()
endforeach()

message("CMAKE_CURRENT_LIST_DIR in FindJson.cmake is: ${CMAKE_CURRENT_LIST_DIR}")

if (UNIX)
    # message("UNIX!")
    foreach(rel_j_dir ${Json_possible_rel_dirs})
        get_filename_component(j_dir ${rel_j_dir} REALPATH BASE_DIR $ENV{HOME})

        set(location "${j_dir}/json.hpp")
        list(APPEND Json_possible_locations ${location})

        if (EXISTS ${location})
            set(found_in_default_dirs ON)
            set(json_location ${location})
            set(json_directory ${j_dir})
        endif()
    endforeach()
endif()

set(internal_json_dir "${CMAKE_CURRENT_LIST_DIR}/../lib/json")
set(internal_path "${internal_json_dir}/json.hpp")
message("internal path: ${internal_path}")
if (EXISTS ${internal_path})
    set(found_in_default_dirs ON)
    set(json_location ${internal_path})
    set(json_directory ${internal_json_dir})
    message("Json found in internal location!")
endif()


if (NOT found_in_default_dirs)
    message(FATAL_ERROR "Json_DIR isn`t specified, can`t also find in default locations (${Json_possible_locations})")
endif()


set(Json_include_directories ${json_directory})

message(STATUS "Package Json successfully found in one of default  locations. Its directory is ${Json_include_directories}")