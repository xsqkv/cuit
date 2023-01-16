// label control class file

#pragma once

#include "cuit.hpp"

class label : public control
{
    std::string text;
    public:
    bool wrap = 0;// abo| -> abo|:ba |
    bool overwriteBorders = 1;//if 1 = abob / if 0 = abo|
    bool wordwrap = 0;// aboba| -> aboba|:boba |
    char8_t charwrap = 0;//if 0 - disabled / count of chars to wrap to new line

    void draw() override
    {
        cli::setText(parent->position.x + position.x, parent->position.y + position.y, text);
        printf("\e[0m");//reset color
    }
    
    void setText(std::string str)
    {
        text = str;
        size = {static_cast<unsigned>(str.size()),1};
        draw();
    }

    label() {}

    label(std::string str)
    {
        text = str;
        size = {static_cast<unsigned>(str.size()),1};
    }
};