#pragma once

#include "sz.h"

class pos
{
    float fx,fy;
    public:
    unsigned x,y;
    
    enum place : char8_t
    {
         TOP_LEFT,      TOP_CENTER,      TOP_RIGHT,




        MIDDLE_LEFT,      CENTER,       MIDDLE_RIGHT,




        BOTTOM_LEFT,   BOTTOM_CENTER,   BOTTOM_RIGHT
    };
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    pos(){}

    pos(unsigned X, unsigned Y, bool normed = 0)
    {
        //if(!x)x=1;
        //if(!y)y=1;
        if(normed) x *= norm;

        x=X;
        y=Y;
    }

    pos(float x, float y, unsigned width, unsigned height, bool normed = 0) : pos(static_cast<int>(width*x),static_cast<int>(height*y),normed) {}
    
    pos(float x, float y, sz size, bool normed = 0)  : pos(static_cast<int>(size.width*x),static_cast<int>(size.height*y),normed) {}
};