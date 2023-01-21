// hsl color area class file

#pragma once

#include <iostream>

class hsv
{
    public:
    double h;
    double s;
    double v;

    // print HSV color
    inline constexpr void print()
    {
        printf("%3.1f %3.1f%% %3.1f%% \n",h,s,v);
    }

    // default constructor
    inline constexpr hsv() : h(0), s(0), v(0) {}

    // setter constructor
    inline constexpr hsv(double H,double S,double V)
    {
        h=H;
        s=S;
        v=V;
    }
};