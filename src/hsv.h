#include<iostream>

class hsv
{
    public:
    double h;
    double s;
    double v;

    inline constexpr void print();

    inline constexpr hsv() : h(0), s(0), v(0) {}

    inline constexpr hsv(double H,double S,double V)
    {
        h=H;
        s=S;
        v=V;
    }
};