#pragma once

#include "sz.h"

class pos
{
    public:
    unsigned x,y;
    
    enum place : char8_t
    {
         TOP_LEFT,      TOP_CENTER,      TOP_RIGHT,




        MIDDLE_LEFT,      CENTER,       MIDDLE_RIGHT,




        BOTTOM_LEFT,   BOTTOM_CENTER,   BOTTOM_RIGHT
    };
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    constexpr inline pos() : x(1),y(1) {}

    constexpr inline pos(unsigned X, unsigned Y, bool normed)
    {
        //if(!x)x=1;
        //if(!y)y=1;
        if(normed) X *= norm;

        x=X;
        y=Y;
    }
};