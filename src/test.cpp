#pragma once
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

int main(int argc,char** argv)
{
    cli::clear();

    circle c({5,5,1},{5,5,1},{"*",9},0);

    c.lj();

    return 0;
}