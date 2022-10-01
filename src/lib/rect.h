#pragma once
#include "shape.h"
#include "cli.h"

class rect : public shape
{
    public:

    constexpr inline void draw() override
    {
        char* clr = ch.getClr();

        char sym = ch.str.c_str()[0];

        for(int x = 1;x < size.width; x++)
        {
            ch.str += sym;
        }

        char* str = ch.getStr();

        std::cerr << clr;

        for(int y = 0;y < size.height; y++)
        {
            cli::setChar(size.width,y+5,str);
        }
    }

    inline rect() : shape() {}

    inline rect(int w,int h) : rect()
    {
        size = {w,h};
    }

    inline rect(sz SIZE) : rect()
    {
        size = SIZE;
    }

    inline rect(int W,int H,cchar CH)
    {
        size = {W,H};
        ch = CH;
    }

    inline rect(sz SIZE,cchar CH)
    {
        size = SIZE;
        ch = CH;
    }
};