#pragma once

#include "control.h"

class label : public control
{
    cchar text;
    public:
    bool wrap = 0;// abo| -> abo|:ba |
    bool overwriteBorders = 1;//if 1 = abob / if 0 = abo|
    bool wordwrap = 0;// aboba| -> aboba|:boba |
    char8_t charwrap = 0;//if 0 - disabled / count of chars to wrap to new line
    
    void print()
    {
        int src = position.x;
        int dst = parent->size.width+overwriteBorders;
        if(src > dst) return;
        printf(text.getClr());
        for(char& ch : text.str) { printf("%c",ch); }
    }

    void draw() override
    {
        cli::setText(parent->position.x + position.x, parent->position.y + position.y, text.str);
        //print();
        printf("\e[0m");//reset color
    }
    
    void setText(cchar str)
    {
        text = str;
        size = sz(strlen(text.getStr()),1);
    }

    label() {}

    label(cchar str)
    {
        text = str;
        size = sz(strlen(text.getStr()),1);
    }
};