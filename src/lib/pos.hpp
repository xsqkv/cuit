// position class file

#pragma once

#include<iostream>

#include "sz.hpp"

class pos
{
    public:
    unsigned x, y;
    bool normed;
    
    enum class place : uint8_t
    {
         TOP_LEFT,      TOP_MIDDLE,      TOP_RIGHT,




        MIDDLE_LEFT,      CENTER,       MIDDLE_RIGHT,




        BOTTOM_LEFT,   BOTTOM_MIDDLE,   BOTTOM_RIGHT
    };
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    constexpr inline pos() : x(1),y(1),normed(1) {}

    constexpr inline pos(unsigned X, unsigned Y, bool Normed) : x(X), y(Y)
    {
        if(Normed)
        {
            x *= norm;
            normed = 1;
        }
        else normed = 0;
    }
};