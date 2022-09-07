#pragma once

#include<iostream>

#include "utils.h"

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
        None,
        Red,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        Silver,
        Gray,
        LRed,
        Lime,
        LYellow,
        Navy,
        Pink,
        LCyan,
        White,
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
        if(foreground && background)
        {
            result += "38;05;" + its(foreground) + ";";
        }
        else if(foreground)
        {
            result += "38;05;" + its(foreground);
        }
        if(background)
        {
            result += "48;05;" + its(background) + "m";
        }
        else
        {
            result += 'm';
        }
        clr = result;
    }

    constexpr inline char* getStr()
    {
        return (char*)(str.c_str());
    }

    constexpr inline char* getClr()
    {
        return (char*)(clr.c_str());
    }

    operator bool() const
    {
        return strlen((char*)str.c_str());
    }

    constexpr inline cchar() : clr(""), str("") {}

    constexpr inline cchar(char ch,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.push_back(ch);
        setColor(foreground,background,style);
    }

    constexpr inline cchar(char* s,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.assign(s);
        setColor(foreground,background,style);
    }

    constexpr inline cchar(const char* s,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.assign(s);
        setColor(foreground,background,style);
    }

    constexpr inline cchar(unsigned foreground, unsigned background, unsigned style)
    {
        setColor(foreground,background,style);
    }
};