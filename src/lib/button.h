#include "control.h"

#pragma once

class button : public control
{
    enum class textAlign : char8_t
    {
        LEFT,
        CENTER,
        RIGHT
    };
};