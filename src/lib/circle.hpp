// circle shape class file

#pragma once
#include "shape.hpp"
#include "cli.hpp"

class circle : public shape
{
    // draw pixel to terminal 
    constexpr inline void drawPixel(int x ,int y, char chr)
    {
        // draw pixel to terminal
        cli::setChar(x + position.x, y * fy + position.y, chr);
    }

    // set 8 points to the terminal
    constexpr inline void Plot8(int x, int y, int R)
    {
        const int nx = R - x;
        const int ny = R - y;
        drawPixel(ny, nx, ch);
        drawPixel(y , nx, ch);
        drawPixel(ny, x , ch);
        drawPixel(y , x , ch);
        drawPixel(nx, ny, ch);
        drawPixel(x , ny, ch);
        drawPixel(nx, y , ch);
        drawPixel(x , y , ch);
    }
    
    // set 4 points to the terminal
    constexpr inline void Plot4(int x, int y, int R)
    {
        const int nx = R - x;
        const int ny = R - y;
        drawPixel(ny, nx, ch);
        //drawPixel(y , nx, ch);
        drawPixel(ny, x , ch);
        //drawPixel(y , x , ch);
        drawPixel(nx, ny, ch);
        //drawPixel(x , ny, ch);
        drawPixel(nx, y , ch);
        //drawPixel(x , y , ch);
    }

    // draw filled circle
    constexpr inline void filled()
    {
        const int R = size.width; // Radius
        const float rq = R / 2.0;

        int x = 0;
        int y = rq; // circle length
        float D = -R * 2; // circulisity

        while (x <= y)
        {
            Plot4(rq + x, rq + y, R);
            D += ++x << 3;
            if(D >= 0) 
            {
                D -= --y << 3;
            }
        }
    }

    // draw empty circle
    constexpr inline void empty()
    {
        const int R = size.width; // Radius
        const float rq = R / 2.0;

        int x = 0;
        int y = rq; // circle length
        float D = -R * 2; // circulisity

        while (x <= y)
        {
            Plot8(rq + x, rq + y, R);
            D += ++x << 3;
            if(D >= 0) 
            {
                D -= --y << 3;
            }
        }
    }

    // ratio height / width
    float fy;
    // is circle filled variable
    bool is_filled;

    public:
    // terminal height / width pixel ratio
    static constexpr float norm = 79.0 / 34.0; // pixel on pixel division

    // draw function
    constexpr inline void draw() override
    {
        is_filled ? filled() : empty(); 
    }

    // default constructor
    inline circle() : shape()
    {
        fy = static_cast<float>(size.height) / static_cast<float>(size.width);
    }

    inline circle(sz SZ, pos POS, bool Filled = 0)
    {
        size = SZ;
        fy = (float)size.height / (float)size.width;
        position = POS;
        is_filled = Filled;
    }

    inline circle(sz SZ, pos POS, char CH, bool Filled = 0)
    {
        size = SZ;
        fy = static_cast<float>(size.height) / static_cast<float>(size.width);
        position = POS;
        ch = CH;
        is_filled = Filled;
    }
};