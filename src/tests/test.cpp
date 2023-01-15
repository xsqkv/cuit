//+==================================+
//| Just a test for current features |
//+==================================+

#include <iostream>

#include "../lib/cuit.hpp"

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