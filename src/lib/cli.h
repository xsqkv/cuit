#pragma once

#include<iostream>

#include <unistd.h> //STDOUT_FILENO in cli::getSize()
#include <sys/ioctl.h> // ioctl // TIOCGWINSZ

#include "sz.h"
#include "cchar.h"

namespace cli
{
    bool cursorVisibility;
    int width;
    int height;

    winsize getSize()
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w;
    }

    sz getSz()
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return sz(w.ws_col,w.ws_row);
    }

    inline void clear()
    {
        printf("\ec");
    }

    inline void hideCursor()
    {
        printf("\e[?25l");
        cursorVisibility = 0;
    }

    inline void showCursor()
    {
        printf("\e[?25h");
        cursorVisibility = 1;
    }

    inline void setCursor(unsigned x, unsigned y)
    {
        printf("\e[%d;%dH",y,x);
    }

    inline void setChar(unsigned x, unsigned y, char* pchr)
    {
        printf("\e[%d;%dH%s",y,x,pchr);
    }

    inline void setText(unsigned x, unsigned y, const char* str)
    {
         printf("\e[%d;%dH%s",y,x,str);
    }

    inline const void setChar(unsigned x, unsigned y, cchar pchr) noexcept(true)
    {
        printf("\e[%d;%dH%s%s",y,x,pchr.getClr(), pchr.getStr());
    }

    inline const void setText(unsigned x, unsigned y, std::string str) noexcept(true)
    {
        printf("\e[%d;%dH%s",y,x,str.c_str());
    }

    inline const void up()
    {
        printf("\e[A");
    }

    inline const void down()
    {
       printf("\e[E");
    }

    inline const void right()
    {
        printf("\e[C");
    }

    inline const void left()
    {
        printf("\e[D");
    }
};