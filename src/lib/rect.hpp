// rectangle shape class control

#pragma once
#include "shape.hpp"
#include "cli.hpp"

class rect : public shape
{
    public:
    
    // static draw rectangle function
    static inline void drawRect(unsigned x, unsigned y, unsigned w, unsigned h, char ch)
    {
        std::string str;

        for(int i = 0; i < h; ++i)
            str += std::string(w, ch) + "\e[1B\e["+std::to_string(w)+"D";

        cli::setText(x, y, str);
    }

    // draw rectangle function
    constexpr inline void draw() override
    {
        // call static draw rectangle function
        drawRect(position.x, position.y, size.width, size.height, ch);
    }

    // default constructor
    inline rect() : shape() {}

    // setter constructor
    inline rect(int w,int h) : rect()
    {
        size = sz(w,h);
    }

    // setter constructor
    inline rect(sz SIZE) : rect()
    {
        size = SIZE;
    }

    // setter constructor
    inline rect(int W,int H,char CH)
    {
        size = sz(W,H);
        ch = CH;
    }

    // setter constructor
    inline rect(sz SIZE,char CH)
    {
        size = SIZE;
        ch = CH;
    }
};