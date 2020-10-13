//
// Created by Vova on 26.05.2020.
//

#pragma once

#include <cassert>

#include <cmath>



// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>


#include <array>
#include <atomic>
#include <chrono>
#include <codecvt>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <ciso646>
#include <shared_mutex>
#include <compare>

#include <json.hpp>

using nlohmann::json;
using namespace std::string_literals;

using namespace std::chrono_literals;
namespace chrono = std::chrono;

// Determine platform:
#ifdef _WIN32
    #define PYTHONIC_IS_WINDOWS
#elif defined(__linux__)
    #define PYTHONIC_IS_LINUX
#else
	#error "Windows or Linux?"
#endif

// Include package for recoding:
#ifdef PYTHONIC_IS_WINDOWS
    #include "windows.h"
#endif

#ifdef PYTHONIC_IS_LINUX
    #include "iconv.h"
#endif



#undef min
#undef max