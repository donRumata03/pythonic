# Defines the following variables:
#
# pythonic_static_libraries <- contains the path to pythonic static library and some supporting libs.
# pythonic_include_directories <- contains a list of directories which you should include in order to use pythonic.

set(actual_pythonic_dir "")
set(pythonic_dir_provided OFF)

#if (EXISTS Pythonic_DIR)
#    message("It`s defined!")
#    message("Pythonic dir is: ${Pythonic_DIR}")
#else()
#    # message(FATAL_ERROR "Variable \"Pythonic_DIR\" isn`t defined. Please define it in order to configure pythonic properly!")
#endif()

set(possible_pythonic_dir_names

        Pythonic_DIR
        pythonic_DIR

        Pythonic_Dir
        pythonic_Dir

        Pythonic_dir
        pythonic_dir

        PYTHONIC_DIR
        )

foreach(current_pythonic_dir_name ${possible_pythonic_dir_names})
    if (EXISTS ${${current_pythonic_dir_name}})
        set(pythonic_dir_provided ON)
        set(actual_pythonic_dir ${${current_pythonic_dir_name}})

    endif()

    # endif()
endforeach()

if(${pythonic_dir_provided})
# message("It`s OK, directory ${Pythonic_DIR} exists!")
#    set(pythonic_dir_provided ON)
#    set(actual_pythonic_dir ${Pythonic_DIR})
else()
    message(FATAL_ERROR "You didn`t provide a directory variable with any of supported names (${possible_pythonic_dir_names}) or the direcory you provided as pythonic_dir doesn`t actually exist!")
endif()


# get_filename_component(j_dir ${rel_j_dir} REALPATH BASE_DIR $ENV{HOME})

file(TO_CMAKE_PATH "${actual_pythonic_dir}/cmake-build-release" Pythonic_release_build_dir)
file(TO_CMAKE_PATH "${actual_pythonic_dir}/cmake-build-debug" Pythonic_debug_build_dir)

# get_filename_component(Pythonic_release_build_dir cmake-build-release REALPATH BASEDIR ${actual_pythonic_dir})
# get_filename_component(Pythonic_debug_build_dir cmake-build-debug REALPATH BASEDIR ${actual_pythonic_dir})

# message(${Pythonic_debug_build_dir})

# Distinguish between build types:
if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(pythonic_build_dir ${Pythonic_release_build_dir})
elseif(${CMAKE_BUILD_TYPE} STREQUAL Debug) # It`s Debug!
    set(pythonic_build_dir ${Pythonic_debug_build_dir})
else()
    message(FATAL_ERROR "Bad CMAKE_BUILD_TYPE (${CMAKE_BUILD_TYPE}). It should be either Release or Debug")
endif()

# Choose static library name based on operation system:
if(UNIX)
    set(pythonic_static_library_name libpythonic.a)
endif()
if(WIN32)
    set(pythonic_static_library_name pythonic.lib)
endif()

if (EXISTS "${pythonic_build_dir}/${pythonic_static_library_name}")
    set(pythonic_static_libraries ${pythonic_build_dir}/${pythonic_static_library_name})
    message("Found pythonic static library here: ${pythonic_static_libraries}")
else()
    message(FATAL_ERROR "Can`t find pythonic static library file in corresponding directory!!! (${pythonic_build_dir}/${pythonic_static_library_name})")
endif()

# STD libs:
if(UNIX)
    list(APPEND pythonic_static_libraries
            tbb
            pthread
            )
endif()

# Include
set(pythonic_include_directories ${actual_pythonic_dir})

# Find Json:
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/CMake")
find_package(Json REQUIRED)
list(APPEND pythonic_include_directories ${Json_include_directories})
message("Pythonic include directories are: ${pythonic_include_directories}")



message(STATUS "Pythonic configuring done.")