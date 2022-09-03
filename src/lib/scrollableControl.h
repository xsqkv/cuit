#include "control.h"

#pragma once

class scrollableControl : public control
{
    public:
    bool inactiveScrollBarsVisibility;
    bool scrollBarsVisibility;
    bool swipeSupport;
    char8_t scrollSpeed = 1;
};