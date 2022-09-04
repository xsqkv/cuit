#pragma once

#include "control.h"
#include "controls.h"



class containerControl : public control
{
    public:
    controls elements;

    containerControl() : control() 
    {
        elements.parent = this->parent;
    }
};