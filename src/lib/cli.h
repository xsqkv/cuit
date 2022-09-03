#include<iostream>

#include <unistd.h> //STDOUT_FILENO in cli::getSize()
#include <sys/ioctl.h> // ioctl // TIOCGWINSZ

#include "sz.h"
#include "cchar.h"

#pragma once

class cli final
{
    public:
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
        std::cout << "\ec";
    }

    inline void hideCursor()
    {
        std::cout << "\e[?25l";
        cursorVisibility = 0;
    }

    inline void showCursor()
    {
        std::cout << "\e[?25h";
        cursorVisibility = 1;
    }

    inline void setCursor(unsigned x, unsigned y)
    {
        std::cout << "\e[" << y << ";" << x << "H";
    }

    inline void setChar(unsigned x, unsigned y, char* pchr)
    {
        std::cout << "\e[" << y << ";" << x << "H" << pchr;
    }

    inline void setChar(unsigned x, unsigned y, const char* pchr)
    {
        std::cout << "\e[" << y << ";" << x << "H" << pchr;
    }

    inline const void setChar(unsigned x, unsigned y, cchar pchr)
    {
        std::cout << "\e[" << y << ";" << x << "H" << pchr.getClr() << pchr.getStr();
    }

    inline const void setChar(unsigned x, unsigned y, std::string str)
    {
        std::cout << "\e[" << y << ";" << x << "H" << str.c_str();
    }

};