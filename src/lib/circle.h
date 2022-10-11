#pragma once
#include "shape.h"
#include "cli.h"

#include<chrono>
#include<thread>
#include<cmath>

class circle : public shape
{
    constexpr inline void Plot8(int x,int y, int R)
    {

        const int nx = R-x;
        const int ny = R-y;

        const int fx = x*norm;
        const int fy = y*norm;

        const int fnx = nx*norm;
        const int fny = ny*norm;

        cli::setChar(fny,nx,ch); // south
        cli::setChar(fy ,nx,ch);
        cli::setChar(fny,x ,ch);
        cli::setChar(fy ,x ,ch);
        cli::setChar(fnx,ny,ch);
        cli::setChar(fx ,ny,ch);
        cli::setChar(fnx,y ,ch);
        cli::setChar(fx ,y ,ch);
    }

    public:

    int f;

    static constexpr double norm = 79.0/34.0; // pixel on pixel division

    constexpr inline void draw() override
    {
        int x = position.x;
        int y = position.y;

        int w = size.width;
        int h = size.height;

        for(int X = x;X < x+w;X++)
        {
            for(int Y = y;Y < y+h;Y++)
            {
                cli::setChar(X,Y,ch);
            }
        }
    }

    constexpr inline void simple()
    {
        int radius = 10;
        int xCenter = 20;
        int yCenter = 20;
        
        int r2 = radius * radius;

        for (int x = -radius; x <= radius; x++)
        {
            int X = (xCenter + x) * norm;
            int y = static_cast<int>(sqrt(r2 - x * x) + 0.5);
            cli::setChar(X, yCenter + y,ch);// reduce to single function
            cli::setChar(X, yCenter - y,ch);
        }
    }

    constexpr inline void lj()
    {
        const double Q = 0.7;
        const int R = 25;// 25 - cube // position of quarter
        const int rq = R * Q;

        int x = 0;
        int y = R * Q;// size
        int D = -50;// - 6 * R; // circulisity

        while (x <= y)
        {
            Plot8(rq + x, rq + y, R * 1.5);
            D += 8 * x + 4;
            if (D >= 0)
            {
                D -= 8 * --y;
            }
            ++x;
        }
    }

    constexpr inline void fill()
    {
        int radius = 10;
        int xCenter = 20;
        int yCenter = 20;
        
        int r2 = radius * radius;

        for (int x = -radius; x < 0; x++)
        {
            int X = (xCenter + x) * norm;
            int y = static_cast<int>(sqrt(r2 - x * x) + 0.5);
            cli::setChar(X, yCenter + y,ch);
            cli::setChar(X, yCenter - y,ch);
        }
    }

    inline circle() : shape() {}

    inline circle(sz SZ, pos POS, cchar CH, int n)
    {
        size = SZ;
        position = POS;
        ch = CH;
        f = n;
    }
};