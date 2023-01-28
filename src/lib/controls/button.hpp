// button control class file

#pragma once

#include "control.hpp"

class button : public control
{
    enum textAlign : uint8_t
    {
        LEFT,
        CENTER,
        RIGHT
    };

    // default constructor
    button() : control() {}
};