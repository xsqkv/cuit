#include "control.h"
#include "controls.h"

#pragma once

class containerControl : public control
{
    public:
    controls elements;

    containerControl() : control() 
    {
        elements.parent = this->parent;
    }
};