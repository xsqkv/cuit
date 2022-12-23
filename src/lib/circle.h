#pragma once
#include "shape.h"
#include "cli.h"

#include <cmath>

class circle : public shape
{
    constexpr inline void Plot8(int x, int y, int R)
    {
        const int nx = R - x;
        const int ny = R - y;
        const int fx = size.normed ? x * norm : x;    // make spaces
        const int fy = size.normed ? y * norm : y;    // make spaces
        const int fnx = size.normed ? nx * norm : nx; // make spaces
        const int fny = size.normed ? ny * norm : ny; // make spaces
        cli::setChar(fny + position.x, nx + position.y, ch);
        cli::setChar(fy + position.x, nx + position.y, ch);
        cli::setChar(fny + position.x, x + position.y, ch);
        cli::setChar(fy + position.x, x + position.y, ch);
        cli::setChar(fnx + position.x, ny + position.y, ch);
        cli::setChar(fx + position.x, ny + position.y, ch);
        cli::setChar(fnx + position.x, y + position.y, ch);
        cli::setChar(fx + position.x, y + position.y, ch);
    }

public:
    int f;
    static constexpr float norm = 79.0 / 34.0; // pixel on pixel division

    constexpr inline void draw() override
    {
        constexpr float R = 20; //* 1.5;// 25 - cube // position of quarter
        constexpr float rq = R / 2;

        float x = 0;
        float y = rq;     // size
        float D = R - 50; // - 6 * R; // circulisity

        while (x <= y)
        {
            Plot8(rq + x, rq + y, R);
            D += x++ * 8;
            if(D >= 0) D -= --y * 8;
        }
    }

    constexpr inline void simple()
    {
        const int R = 10;
        int xCenter = 20;
        int yCenter = 20;

        constexpr int r2 = R * R;

        for (int x = -R; x <= R; x++)
        {
            int X = (xCenter + x) * norm;
            int y = static_cast<int>(sqrt(r2 - x * x) + 0.5);
            cli::setChar(X, yCenter + y, ch); // reduce to single function
            cli::setChar(X, yCenter - y, ch);
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