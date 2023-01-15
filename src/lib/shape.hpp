// shape class file

#pragma once
#include "sz.hpp"
#include "cchar.hpp"
#include "pos.hpp"

class shape
{
    public:
    cchar ch;
    sz size;
    pos position;

    constexpr inline virtual void draw() = 0;

    inline shape() : size({5,5,1}) , ch("#") {}

    inline shape(sz SIZE, cchar CH)
    {
        ch = CH;
        size = SIZE;
    }

    inline shape(int w, int h, cchar CH)
    {
        ch = CH;
        size = sz(w,h);
    }
};