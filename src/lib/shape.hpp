// shape class file

#pragma once
#include "sz.hpp"
#include "pos.hpp"

class shape
{
    public:
    char ch;
    sz size;
    pos position;

    // virtual draw function
    constexpr inline virtual void draw() = 0;

    // default constructor
    inline shape() : size({5,5,1}) , ch('#') {}

    // setter constructor
    inline shape(sz SIZE, char CH)
    {
        ch = CH;
        size = SIZE;
    }

    // setter constructor
    inline shape(int w, int h, char CH)
    {
        ch = CH;
        size = sz(w,h);
    }
};