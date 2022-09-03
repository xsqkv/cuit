#include <iostream>

#pragma once

class hsv
{
    public:
    double h;
    double s;
    double v;

    inline constexpr void print()
    {
        printf("%3.1f %3.1f%% %3.1f%% \n",h,s,v);
    }

    inline constexpr hsv() : h(0), s(0), v(0) {}

    inline constexpr hsv(double H,double S,double V)
    {
        h=H;
        s=S;
        v=V;
    }
};