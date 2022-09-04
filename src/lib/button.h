#pragma once

#include "control.h"

class button : public control
{
    enum class textAlign : char8_t
    {
        LEFT,
        CENTER,
        RIGHT
    };
};