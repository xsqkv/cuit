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

    window w({25,25,1},{5,5,0});

    label l("label");
    
    l.position = {1,1,0};

    w.settings.fill = ':';
    //w.settings.topBar = '-';
    //w.settings.leftBar = '|';
    //w.settings.rightBar = '|';
    //w.settings.downBar = '-';
    //w.settings.leftTopCorner = '+';
    //w.settings.rightTopCorner = '+';
    //w.settings.leftDownCorner = '+';
    //w.settings.rightDownCorner = '+';

    w.addControl(l);
    //w.addControl(l);
    //for(int i = 0;i < 8000; ++i)
        w.show();

    //getchar();

    return 0;
}