#include <iostream>
#include "lib/cuit.h"


namespace bt
{
    inline void st(short& num,uint8_t idx)
    {
        idx--;
        num |= 1 << idx;
    }

    inline void ust(short& num,uint8_t idx)
    {
        idx--;
        num &= ~(1<<idx);
    }

    inline bool get(short num,uint8_t idx)
    {
        idx--;
        return 1 << idx & num;
    }

    inline void prnt(short num)
    {
        std::string str("");
        for(int i = 0;i < sizeof(short);i++)
        {
            for(int j = 0;j < 8;j++)
            {
                str = its(num % 2) + str;
                num >>= 1;
            }
        }
        std::cerr<<str<<'\n';
    }
}

void draw()
{
    int x = 5, y = 5;
    int w = 100, h = 100;

    for(int X = x;X < x+w;X++)
    {
        for(int Y = y;Y < y+h;Y++)
        {
            cli::setChar(X,Y,'*');
        }
    }
}

void odraw()
{
    int x = 5, y = 5;
    int w = 100, h = 100;

    char sym = '*';
    string str;

    for(int X = 0;X < w; X++)
    {
        str += sym;
    }

    for(int Y = y;Y < y+h; Y++)
    {
        cli::setChar(x,Y,str);
    }
}

int main(int argc,char** argv)
{
    cli::clear();
//
    //circle c({5,5,1},{5,5,1},{"#",9},0);
//
    //c.paint();
//
    //getchar();

    //debug::time(draw);
    debug::time(odraw);

    return 0;
}
