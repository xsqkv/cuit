// debug namespace file

#pragma once 

#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

namespace debug
{
    template<class t>
    constexpr inline double time(t a(...)) noexcept(true)
    {
        auto start = system_clock::now();
        a();
        auto end = system_clock::now();

        double time = static_cast<double>((end - start).count()) / 1000000.0;
        
        //cerr << time << " ms\n";

        return time;
    }

    template<class t>
    constexpr inline void compare(t a(...), t b(...)) noexcept(true)
    {
        //Function 1
        printf("Function 1: ", time(a));
        //Function 2
        printf(" ms\tFunction 2: ",time(b), " ms\n");
    }

    inline void var_test() noexcept(true)
    {
        printf("       char: %lu bytes\n",sizeof(char));
        printf("    wchar_t: %lu bytes\n",sizeof(wchar_t));
        printf("\n");
        printf("      short: %lu bytes\n",sizeof(short));
        printf("        int: %lu bytes\n",sizeof(int));
        printf("       long: %lu bytes\n",sizeof(long));
        printf("  long long: %lu bytes\n",sizeof(long long));
        printf("\n");
        printf("      float: %lu bytes\n",sizeof(float));
        printf("     double: %lu bytes\n",sizeof(double));
        printf("long double: %lu bytes\n\n",sizeof(long double));
    }
}