#pragma once

class sz
{
    public:
    unsigned width, height;
    bool normed;
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    public:
    sz() : width(5),height(5),normed(1) {}

    sz(unsigned w, unsigned h, bool Normed = 0)
    {
        if(Normed)
        {
            w *= norm;
            normed = 1;
        } else normed = 0;
        width = w;
        height = h;
    }
};