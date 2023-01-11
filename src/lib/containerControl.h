// container control class file

#pragma once
#include<vector>

#include "control.h"


class containerControl : public control
{
    public:
    std::vector<control*> elements;

    void add(control* ctrl)
    {   
        ctrl->parent = this;
        elements.push_back(ctrl);
    }

    containerControl() : control() {}
};