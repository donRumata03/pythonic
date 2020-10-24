# Defines the following variables:
#
# pythonic_static_library <- contains the path to pythonic static library.
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
    # message(${current_pythonic_dir_name})
    # if (NOT DEFINED ${current_pythonic_dir_name})

    # else()
        # message("${current_pythonic_dir_name} is defined")
        # message(${${current_pythonic_dir_name}})
    if (EXISTS ${${current_pythonic_dir_name}})
        # message("Provided dir exists!")

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



set(Pythonic_release_build_dir ${actual_pythonic_dir}/cmake-build-release)
set(Pythonic_debug_build_dir ${actual_pythonic_dir}/cmake-build-debug)

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
    set(pythonic_static_library ${pythonic_build_dir}/${pythonic_static_library_name})
    message("Found pythonic static library here: ${pythonic_static_library}")
else()
    message(FATAL_ERROR "Can`t find pythonic static library file in corresponding directory!!! (${pythonic_build_dir}/${pythonic_static_library_name})")
endif()

set(pythonic_include_directories ${actual_pythonic_dir})

# Find Json:
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/CMake")
find_package(Json REQUIRED)
list(APPEND pythonic_include_directories ${Json_include_directories})
message("Pythonic include directories are: ${pythonic_include_directories}")



message(STATUS "Pythonic configuring done.")