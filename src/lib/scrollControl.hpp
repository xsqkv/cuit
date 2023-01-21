// scrollable control class file

#pragma once

#include "control.hpp"

class scrollControl : public control
{
    public:
    bool inactiveScrollBarsVisibility;
    bool scrollBarsVisibility;
    bool swipeSupport;
    char8_t scrollSpeed;

    // default constructor
    scrollControl() : control(),inactiveScrollBarsVisibility(0), scrollBarsVisibility(0), swipeSupport(0), scrollSpeed(1) { }
};