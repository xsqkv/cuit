// circle shape class file

#pragma once
#include "shape.hpp"
#include "cli.hpp"

#include <cmath>

class circle : public shape
{
    constexpr inline void drawPixel(int x ,int y, cchar chr)
    {
        if(size.normed){
            cli::setChar(x + position.x, y * fy + position.y, chr);
        }else{
            cli::setChar(x + position.x, y * fy + position.y, chr);
        }
    }

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

    constexpr inline void filled()
    {
        int R = size.width; // Radius
        float rq = R / 2.0;

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

    constexpr inline void empty()
    {
        int R = size.width; // Radius
        float rq = R / 2.0;

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

    float fy;
    bool is_filled;

    public:
    static constexpr float norm = 79.0 / 34.0; // pixel on pixel division

    constexpr inline void draw() override
    {
        is_filled ? filled() : empty(); 
    }

    inline circle() : shape() { fy = (float)size.height / (float)size.width; }

    inline circle(sz SZ, pos POS, bool Filled = 0)
    {
        size = SZ;
        fy = (float)size.height / (float)size.width;
        position = POS;
        is_filled = Filled;
    }

    inline circle(sz SZ, pos POS, cchar CH, bool Filled = 0)
    {
        size = SZ;
        fy = (float)size.height / (float)size.width;
        position = POS;
        ch = CH;
        is_filled = Filled;
    }
};