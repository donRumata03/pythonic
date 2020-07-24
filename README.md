# Pythonic
It\`s a C++ library which provides basic 
I use it in all of my C++ projects in order to simplify all aspects of work.

## Usage:
This library uses CMake as build system.
To use this library you probably need to build it for you platform and compiler. 
However, there are some binary files in "cmake-build-debug" and "cmake-build-release" (.exe and .lib)

There are no additional dependencies, so, you should simply run CMake.
After that, *.lib files for Release or Debug mode appear in the corresponding locations.
To use it from other libraries or executables you should type 
    `set(Pythonic_DIR ${LOCATION_OF_THE_ROOT_FOLDER_OF_PYTHONIC})`
in you CMake file. And after that:
    `find_package(Pythonic required)` 

"pythonic_static_library" variable will contain the name of the library you should link against.
"pythonic_include_directories" variable will contain the list of directories you should add to you include directory index.

So, you should write this lines:

    include_directories(${pythonic_include_directories})
    target_link_libraries(${YOUR_TARGET_NAME} ${pythonic_static_library})


## Features:
- Utilities for displaying (in "./displaying/" folder):
    - STL containers stream output operators
    - Type name getter function, returns std::string, pays respect to pointers, references, specifiers and qualifiers
    - ANSI colors in console (see)
- Multidimensional Array class with slicing support (see n_dim/nd_array.h)
- Tools to deal with encodings (in "./encoding/" folder):
    - My C++ wrapper around WinAPI for converting between UTF-8, UTF-16 (windows system encoding), and CP-1251 (one-byte cyrillic encoding)
    - Automatic encoding determination (UTF-8, CP-1251 and pure ASCII)
    - Automatic recoding to one of those encodings (UTF-8, CP-1251 and pure ASCII)
- Utilities to deal with letters
- All of the features ^^^ above ^^^ are covered by tests (in folder with corresponding name)
