// rectangle shape class control

#pragma once
#include "shape.hpp"
#include "cli.hpp"

class rect : public shape
{
    public:

    static void drawRect(unsigned x, unsigned y, unsigned w, unsigned h, char ch)
    {
        std::string str;

        for(int i = 0; i < h; ++i)
            str += std::string(w, ch) + "\e[1B\e["+std::to_string(w)+"D";

        cli::setText(x, y, str);
    }

    constexpr inline void draw() override
    {
        std::string str;

        for(int i = 0; i < size.height; ++i)
            str += std::string(size.width, ch) + "\e[1B\e["+std::to_string(size.width)+"D";

        cli::setText(position.x, position.y, str);
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

    inline rect(int W,int H,char CH)
    {
        size = sz(W,H);
        ch = CH;
    }

    inline rect(sz SIZE,char CH)
    {
        size = SIZE;
        ch = CH;
    }
};