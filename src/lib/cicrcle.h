#pragma once
#include "shape.h"
#include "cli.h"

class circle : public shape
{
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

    constexpr inline void paint()
    {
        double R = 50; // Radius
        int X1 = 130,Y1 = 70;// Coordinates of center

        int x = 0,y = R; // inner temp variables

        int delta = 1 - 2 * R;
        int error = 0;

        while (y >= x)
        {
            cli::setChar((X1 + x)*norm, Y1 + y,ch);
            cli::setChar((X1 + x)*norm, Y1 - y,ch);
            cli::setChar((X1 - x)*norm, Y1 + y,ch);
            cli::setChar((X1 - x)*norm, Y1 - y,ch);
            cli::setChar((X1 + y)*norm, Y1 + x,ch);
            cli::setChar((X1 + y)*norm, Y1 - x,ch);
            cli::setChar((X1 - y)*norm, Y1 + x,ch);
            cli::setChar((X1 - y)*norm, Y1 - x,ch);

            error = 2 * (delta + y) - 1;

            if ((delta < 0) && (error <= 0))
            {
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0))
            {
                delta -= 2 * --y + 1;
                continue;
            }

            delta += 2 * (++x - --y);
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