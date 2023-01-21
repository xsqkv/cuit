// console line interface namespace file

#pragma once

#include<iostream>

#include <unistd.h> //STDOUT_FILENO in cli::getSize()
#include <sys/ioctl.h> // ioctl // TIOCGWINSZ

#include "sz.hpp"

class cli
{
    public:

    #pragma region Properties

    static bool cursorVisibility;
    static int width;
    static int height;

    #pragma endregion

    #pragma region Enums

    enum styles : uint8_t
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

    enum sysColors : uint8_t
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
        White
    };

    #pragma endregion

    #pragma region Methods
    
    // get console control color sequence
    static std::string getColor(unsigned foreground, unsigned background, unsigned style)
    {
        // minimal reqs "\e[01;38;05;10mUSAS\e[m112"

        std::string result = "\e[";
        if(style)
        {   
            if(style & 1  ) { result += "01";  style -= 1;   if(style) result += ';'; }
            if(style & 2  ) { result += "02";  style -= 2;   if(style) result += ';'; }
            if(style & 4  ) { result += "03";  style -= 4;   if(style) result += ';'; }
            if(style & 8  ) { result += "04";  style -= 8;   if(style) result += ';'; }
            if(style & 16 ) { result += "05";  style -= 16;  if(style) result += ';'; }
            if(style & 32 ) { result += "06";  style -= 32;  if(style) result += ';'; }
            if(style & 64 ) { result += "07";  style -= 64;  if(style) result += ';'; }
            if(style & 128) { result += "08";  style -= 128;                          }

            if(foreground) result += ';';
            else result += 'm';
        }
        if(foreground)
        {
            result += "38;05;" + std::to_string(foreground);

            if(background) result += ';';
            else result += 'm';
        }
        if(background)
        {
            result += "48;05;" + std::to_string(background) + 'm';
        }
        return result;
    }

    // write console control color sequence in console
    static void beginColor(unsigned foreground, unsigned background, unsigned style)
    {
        printf("%s",getColor(foreground,background,style).c_str());
    }
    
    // write console control reset color sequence in console
    static void endColor()
    {
        printf("%s","\e[m");
    }

    // get terminal buffer size
    static inline winsize getSize()
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w;
    }

    // get terminal buffer size to sz format
    static inline sz getSz()
    {
        auto w = getSize();
        return sz(w.ws_col,w.ws_row);
    }

    // clear CCS
    static inline void clear()
    {
        printf("\ec");
    }

    // hide cursor CCS
    static inline void hideCursor()
    {
        printf("\e[?25l");
        cursorVisibility = 0;
    }

    // show cursor CCS
    static inline void showCursor()
    {
        printf("\e[?25h");
        cursorVisibility = 1;
    }

    // set cursor CCS
    static inline void setCursor(unsigned x, unsigned y)
    {
        printf("\e[%d;%dH",y,x);
    }

    // set cursor CCS and write char
    static inline const void setChar(unsigned x, unsigned y, char ch) noexcept(true)
    {
        printf("\e[%d;%dH%c",y,x,ch);
    }

    // set cursor CCS and write text
    static inline const void setText(unsigned x, unsigned y, std::string str) noexcept(true)
    {
        printf("\e[%d;%dH%s",y,x,str.c_str());
    }

    // write CCS UP
    static inline const void up()
    {
        printf("\e[A");
    }

    // write CCS DOWN
    static inline const void down()
    {
       printf("\e[E");
    }

    // write CCS RIGHT
    static inline const void right()
    {
        printf("\e[C");
    }

    // write CCS LEFT
    static inline const void left()
    {
        printf("\e[D");
    }

    #pragma endregion

};