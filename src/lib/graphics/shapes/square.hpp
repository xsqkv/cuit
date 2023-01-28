// square class file

#pragma once
#include "../../pos.hpp"
#include "../../cli.hpp"

class square
{
    public:
    char ch;
    unsigned n;
    pos position;
    bool normed;
    static constexpr float coef = 79.0/34.0; // pixel on pixel division

    // static draw function
    static constexpr inline void draw(pos Position, unsigned N, char CH)
    {
        std::string str;
        const unsigned W = N * coef;
        
        for(int i = 0; i < N; ++i)
            str += std::string(W, CH) + "\e[1B\e["+std::to_string(W)+"D";

        cli::setText(Position.x, Position.y, str);
    } 

    // draw function
    constexpr inline void draw()
    {
        // call static draw function
        draw(position, n, ch);
    }

    // setter constructor
    constexpr inline square(pos POS={5,5,1}, int N=5, char CH='#', bool Normed=1)
    {
        position = POS;
        n = N;
        ch = CH;
        normed = Normed;
    }
};