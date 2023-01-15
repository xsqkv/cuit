// window settings class file

#pragma once

#include "cchar.hpp"

class windowSettings
{
    public:
    enum class windowStyles : char8_t
    {
        SOLID,
        BORDERED,
        BORDERED_CORNERED,
        RECT,
        SMOOTH,
    };
    
    cchar fill{""};

    cchar borders{""};

    cchar corners{""};

    cchar hBar{""};
    cchar vBar{""};

    cchar topBar{""};
    cchar leftBar{""};
    cchar rightBar{""};
    cchar downBar{""};

    cchar leftTopCorner{""};
    cchar rightTopCorner{""};
    cchar leftDownCorner{""};
    cchar rightDownCorner{""};

    windowSettings()
    {

    }
};