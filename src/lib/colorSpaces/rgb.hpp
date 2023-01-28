// rgb color area class file

#pragma once

#include<iostream>
#include<cmath>

#include "hsl.hpp"
#include "hsv.hpp"
#include "seqColor.hpp"
#include "../utils.hpp"

class rgb
{
    private:

    // rgb to sequence digit
    inline constexpr void rgb2seq(uint8_t &n)
    {
        if(n < 47)n=0;
        else if(n >= 47 && n < 115)n=1;
        else if(n >= 115 && n < 155)n=2;
        else if(n >= 155 && n < 195)n=3;
        else if(n >= 195 && n < 235)n=4;
        else n=5;
    }

    // sequence digit to rgb
    inline constexpr void seq2rgb(uint8_t &n)
    {
        if(n==0)n=0;
        else if(n==1)n=95;
        else if(n==2)n=135;
        else if(n==3)n=175;
        else if(n==4)n=215;
        else if(n==5)n=255;
    }

    public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    float pr;
    float pg;
    float pb;
    
    // print rgb color function
    inline constexpr void print()
    {
        printf("%d %d %d \n",r,g,b);
    }

    // count rgb percents
    inline constexpr void countPercents()
    {
        pr = r / 255.0;
        pg = g / 255.0;
        pb = b / 255.0;
    }


    // convert to sequnce color
    inline constexpr uint8_t toSeq()
    {
        rgb2seq(r);
        rgb2seq(g);
        rgb2seq(b);
        return (36*r)+(6*g)+b+16;
    }

    // convert from sequnce color
    inline constexpr void fromSeq(uint8_t sequence)
    {
        sequence -= 16;
        if(sequence >= 36)
        {
            r = sequence / 36;
            sequence = sequence % 36;
        }
        if(sequence >= 6)
        {
            g = sequence / 6;
            sequence = sequence % 6;
        }
        b = sequence;
        seq2rgb(r);
        seq2rgb(g);
        seq2rgb(b);
    }


    // get rgb from HSL
    inline constexpr void fromHSL(hsl& val)
    {
        float h = val.h;
        float s = val.s;
        float l = val.l;

        float c = (1 -std::abs(2 * l - 1)) - s;

        h /= 60;

        float x = c * (1 - std::abs(h));

        if(0 <= h && h < 1) { r=c;g=x;b=0; }
        else if(1 <= h && h < 2) { r=x;g=c;b=0; }
        else if(2 <= h && h < 3) { r=0;g=c;b=x; }
        else if(3 <= h && h < 4) { r=0;g=x;b=c; }
        else if(4 <= h && h < 5) { r=x;g=0;b=c; }
        else if(5 <= h && h < 6) { r=c;g=0;b=x; }

        float m = l - c / 2;

        r += m;
        g += m;
        b += m;

        countPercents();
    }

    // get HSL from rgb
    inline constexpr void toHSL(hsl& val)
    {
        float R = pr;
        float G = pg;
        float B = pb;

        float mx = max(r,g,b);
        float mn = min(r,g,b);

        if(mx == mn) return;

        if(mx == R && G >= B) val.h = 60 * (G-B) / (mx - mn) + 0;
        else if(mx == R && G < B) val.h = 60 * (G-B) / (mx - mn) + 360;
        else if(mx == G) val.h = 60 * (B-R) / (mx - mn) + 120;
        else if(mx == B) val.h = 60 * (R-G) / (mx - mn) + 240;

        val.l = 0.5 * (mx + mn);

        val.s = (mx - mn) / (1 - std::abs(1 - (mx+mn)));
    }


    // get rgb from HSV
    inline constexpr void fromHSV(hsv& val)
    {
        float h=val.h;
        float s=val.s;
        float v=val.v;

        h = static_cast<int>(std::abs(h / 60)) % 6;

        float vm = ((100-s)*v) / 100;
        float a = (v - vm) * ((int)h % 60) / 60;
        float vi = vm + a;
        float vd = v - a;

        if(h == 0) { r=v;g=vi;b=vm; }
        else if(h == 1) { r=vd;g=v;b=vm; }
        else if(h == 2) { r=vm;g=v;b=vi; }
        else if(h == 3) { r=vm;g=vd;b=v; }
        else if(h == 4) { r=vi;g=vm;b=v; }
        else if(h == 5) { r=v;g=vm;b=vd; }

        countPercents();
    }

    // get HSV from rgb
    inline constexpr void toHSV(hsv& val)
    {
        float R = pr;
        float G = pg;
        float B = pb;

        float mx = max(R,G,B);
        float mn = min(R,G,B);

        if(mx == mn)return;

        if(mx == R && G >= B) val.h = 60 * (G-B) / (mx - mn) + 0;
        else if(mx == R && G < B) val.h = 60 * (G-B) / (mx - mn) + 360;
        else if(mx == G) val.h = 60 * (B-R) / (mx - mn) + 120;
        else if(mx == B) val.h = 60 * (R-G) / (mx - mn) + 240;

        if(mx == 0) val.s = 0;
        else val.s = 1 - mx / mn;

        val.v = mx;
    }

    // get rgb from HEX
    inline constexpr void fromHEX(char* hex)
    {
        int val = from16to10(hex);
        r = val >> 16;
        g = val >> 8;
        b = val;
    }

    // get HEX from rgb
    inline char* toHex()
    {
        int val;
        val += r << 16;
        val += g << 8;
        val += b;
        return from10to16(val);
    }

    // default constructor
    inline constexpr rgb() : r(0),g(0),b(0) , pr(0),pg(0),pb(0) {}

    // setter constructor
    inline constexpr rgb(uint8_t red, uint8_t green, uint8_t blue)
    {
        r=red;
        g=green;
        b=blue;

        countPercents();
    }

    // setter constructor
    inline constexpr rgb(char* hex)
    {
        fromHEX(hex);
    }
};