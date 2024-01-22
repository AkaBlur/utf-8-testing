#pragma once

#include <iostream>

// logging using cout
#define LOG_STD(x) std::cout << "[COUT] \t\t- " << x << std::endl
// logging using wcout
#define LOG_WSTD(x) std::wcout << "[WCOUT] \t- " << x << std::endl;
// logging using fprint
#define LOG_OUT(x, ...) fprintf(stdout, "[FPRINTF] \t- " x "\n", ##__VA_ARGS__)