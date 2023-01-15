// button control class file

#pragma once

#include "control.hpp"

class button : public control
{
    enum class textAlign : char8_t
    {
        LEFT,
        CENTER,
        RIGHT
    };
};