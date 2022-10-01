#pragma once
#include "cchar.h"
#include "pos.h"
#include "cli.h"

class square
{
    public:
    cchar ch;
    int n;
    pos Pos;
    bool norm;
    static constexpr float coef = 79.0/34.0; // pixel on pixel division

    constexpr inline void draw()
    {
        int x;
        if(norm) x = n * coef;
        else x = n;

        std::string xline;

        for(int i=0;i < x;i++)
        {
            xline += ch.getStr();
        }

        for(int y = Pos.y; y < Pos.y+n;y++)
        {
            cli::setChar(Pos.x,y,xline);
        }
    }

    constexpr inline square(int N=5, bool normed=1, cchar CH={"#"},pos POS={5,5,1})
    {
        ch = CH;
        n = N;
        Pos = POS;
        norm=normed;
    }
};