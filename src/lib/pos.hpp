// position class file

#pragma once

#include<iostream>

#include "sz.hpp"

class pos
{
    public:
    unsigned x, y;
    
    enum class place : uint8_t
    {
         TOP_LEFT,      TOP_MIDDLE,      TOP_RIGHT,




        MIDDLE_LEFT,      CENTER,       MIDDLE_RIGHT,




        BOTTOM_LEFT,   BOTTOM_MIDDLE,   BOTTOM_RIGHT
    };
    
    // terminal height / width pixel ratio
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    //default constructor
    constexpr inline pos() : x(1),y(1) {}

    // setter constructor
    constexpr inline pos(unsigned X, unsigned Y, bool Normed) : x(X), y(Y)
    {
        // if position normed multiply X on height/width ratio
        if(Normed) x *= norm;
    }
};