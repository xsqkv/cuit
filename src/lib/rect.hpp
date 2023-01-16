// rectangle shape class control

#pragma once
#include "shape.hpp"
#include "cli.hpp"

class rect : public shape
{
    public:

    constexpr inline void draw() override
    {
        std::string str;

        for(int x = 1;x < size.width; ++x) str += ch;

        cli::setColor(10,0,1);

        for(int y = 0;y < size.height; ++y) cli::setText(size.width,y+5,str);
    }

    inline rect() : shape() {}

    inline rect(int w,int h) : rect()
    {
        size = sz(w,h);
    }

    inline rect(sz SIZE) : rect()
    {
        size = SIZE;
    }

    inline rect(int W,int H,char8_t CH)
    {
        size = sz(W,H);
        ch = CH;
    }

    inline rect(sz SIZE,char8_t CH)
    {
        size = SIZE;
        ch = CH;
    }
};