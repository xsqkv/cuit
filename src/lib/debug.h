#pragma once 

#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

namespace debug
{
    constexpr inline double time(void a())
    {
        auto start = system_clock::now();
        a();
        auto end = system_clock::now();

        double time = static_cast<double>((end - start).count()) / 1000000.0;
        
        //cerr << time << " ms\n";

        return time;
    }

    constexpr inline void compare(void a(), void b())
    {
        //Function 1
        cerr << "Function 1: " << time(a);
        //Function 2
        cerr << " ms\tFunction 2: " << time(b) << " ms\n";
    }

    constexpr inline void var_test()
    {
        cerr << "       char: " << sizeof(char) << " bytes\n";
        cerr << "    wchar_t: " << sizeof(wchar_t) << " bytes\n";
        cerr << '\n';
        cerr << "      short: " << sizeof(short) << " bytes\n";
        cerr << "        int: " << sizeof(int) << " bytes\n";
        cerr << "       long: " << sizeof(long) << " bytes\n";
        cerr << "  long long: " << sizeof(long long) << " bytes\n";
        cerr << '\n';
        cerr << "      float: " << sizeof(float) << " bytes\n";
        cerr << "     double: " << sizeof(double) << " bytes\n";
        cerr << "long double: " << sizeof(long double) << " bytes\n\n";
    }
}