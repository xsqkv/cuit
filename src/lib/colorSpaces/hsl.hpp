// hsl color area class file

#pragma once

#include<iostream>
#include<cmath>

#include "hsv.hpp"

class hsl
{
    public:
    double h;
    double s;
    double l;

    // print HSL colors
    inline constexpr void print()
    {
        printf("%3.1f %3.1f%% %3.1f%% \n",h,s,l);
    }

    // get HSL from HSV
    inline constexpr void fromHSV(hsv& x)
    {
        h = x.h;
        l = x.v * (1 - x.v / 2);
        if(l == 0 || l == 1) s = 0;
        else s = (x.v - l) / std::min(l, 1 - l);
    }

    // from HSV to HSL
    inline constexpr void toHSV(hsv& x)
    {
        double hh = h;
        double ss = s / 100;
        double ll = l / 100;

        x.h = hh;
        hh *= 2;
        if(ll <= 1) ss *= ll;
        else ss *= 2 - ll;
        x.v = (ll + ss) / 2;
        x.s = (2*ss) / (ll + ss);

        x.s = round(x.s * 100.0);
        x.v = round(x.v * 100.0);
    }

    // default constructor
    inline constexpr hsl() : h(0), s(0), l(0) {}

    // setter constructor
    inline constexpr hsl(double H,double S,double L) : h(H), s(S), l(L) {}
};
