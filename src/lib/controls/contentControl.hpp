// container control class file

#pragma once
#include<vector>

#include "control.hpp"

class contentControl : public control
{
    public:
    // child poiner array
    std::vector<control*> childs;

    virtual void show(bool) {}

    // add control to the content control
    void inline addControl(control& ctrl) noexcept
    {   
        ctrl.parent = this;
        childs.push_back(&ctrl);
    }

    // remove control from content control
    void inline removeControl(control& ctrl) noexcept
    {
        delete &ctrl;
    }

    // default constructor
    contentControl() : control() {}
};