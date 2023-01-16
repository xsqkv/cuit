// shape class file

#pragma once
#include "sz.hpp"
#include "pos.hpp"

class shape
{
    public:
    char8_t ch;
    sz size;
    pos position;

    constexpr inline virtual void draw() = 0;

    inline shape() : size({5,5,1}) , ch('#') {}

    inline shape(sz SIZE, char8_t CH)
    {
        ch = CH;
        size = SIZE;
    }

    inline shape(int w, int h, char8_t CH)
    {
        ch = CH;
        size = sz(w,h);
    }
};