// scrollable control class file

#pragma once

#include "control.hpp"

class scrollableControl : public control
{
    public:
    bool inactiveScrollBarsVisibility;
    bool scrollBarsVisibility;
    bool swipeSupport;
    char8_t scrollSpeed = 1;
};