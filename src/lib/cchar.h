#include<iostream>

#include "utils.h"

#pragma once

class cchar
{
    protected:
    std::string clr;
    std::string str;
    
    public:
    enum class style : char8_t
    {
        Bold = 1,
        Low_Intensity = 2,
        Italic = 4,
        Underline =8,
        Blinking=16,
        Reverse=32,
        Background=64,
        Invisible=128
    };
    enum class sysColors : char8_t
    {
        Black,
        Maroon,
        Green,
        Olive,
        Navy,
        Purple,
        Teal,
        Silver,
        Grey,
        Red,
        Lime,
        Yellow,
        Blue,
        Fuchsia,
        Aqua,
        White
    };

    void setColor(unsigned foreground, unsigned background, unsigned style)
    {
        std::string result = "\e[";
        if(style)
        {   
            if(style & 1)result += "01;";
            if(style & 2)result += "02;";
            if(style & 4)result += "03;";
            if(style & 8)result += "04;";
            if(style & 16)result += "05;";
            if(style & 32)result += "06;";
            if(style & 64)result += "07;";
            if(style & 128)result += "08;";
        }  
        result += "38;05;" + its(foreground) + ";";
        result += "48;05;" + its(background) + "m";
        clr = result;
    }

    char* getStr()
    {
        return (char*)(str.c_str());
    }

    char* getClr()
    {
        return (char*)(clr.c_str());
    }

    operator bool() const
    {
        return strlen((char*)str.c_str());
    }

    cchar() : clr(""), str("") {}

    cchar(char ch,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.push_back(ch);
        setColor(foreground,background,style);
    }

    cchar(char* s,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.assign(s);
        setColor(foreground,background,style);
    }

    cchar(const char* s,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.assign(s);
        setColor(foreground,background,style);
    }

    cchar(unsigned foreground, unsigned background, unsigned style)
    {
        setColor(foreground,background,style);
    }
};