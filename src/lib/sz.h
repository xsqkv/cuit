
#pragma once

class sz
{
    public:
    unsigned width;
    unsigned height;
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    public:
    sz(){}

    sz(unsigned w, unsigned h, bool normed = 0)
    {
        if(normed) w *= norm;
        width = w;
        height = h;
    }
};