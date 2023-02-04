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

    window w({15,15,1},{4,4,1});

    label l("label");
    
    l.position = {5,5,1};

    w.settings.fill = '.';
    w.settings.setHBars('=');   
    w.settings.setVBars('|');
    w.settings.setLeftCorners('<');
    w.settings.setRightCorners('0');

    w.addControl(l);

    w.show(1);

    getchar();

    return 0;
}