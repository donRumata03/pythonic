//
// Created by Vova on 14.10.2020.
//

#pragma once

#include "pythonic_pch.h"

#ifdef PYTHONIC_IS_WINDOWS
	#include "files/platform/windows/file_reader_windows.h"
#else
	#include "files/platform/linux/file_reader_linux.h"
#endif