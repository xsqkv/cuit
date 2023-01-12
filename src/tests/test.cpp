//+==================================+
//| Just a test for current features |
//+==================================+

#include <iostream>

#include "../lib/cuit.h"

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
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cerr.tie(nullptr);
    clog.tie(nullptr);

    cli::clear();

    window w({20,15,1},{5,5,1});

    label l(cchar("label",10,0,0));
    
    l.position = {1,1,0};

    w.settings.fill = ".";

    w.addControl(l);
    //w.addControl(l);
    for(int i=0;i<1000;++i)
        w.show();

    //getchar();

    return 0;
}