// size class file

#pragma once

class sz
{
    public:
    unsigned width, height;
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    public:

    // default constructor
    sz() : width(5),height(5){}

    // setter constructor
    sz(unsigned w, unsigned h, bool Normed = 0)
    {
        if(Normed) w *= norm;
        width = w;
        height = h;
    }
};