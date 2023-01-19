// container control class file

#pragma once
#include<vector>

#include "control.hpp"


class contentControl : public control
{
    public:
    std::vector<control*> childs;

    void inline addControl(control& ctrl) noexcept
    {   
        ctrl.parent = this;
        childs.push_back(&ctrl);
    }

    void inline removeControl(control& ctrl) noexcept
    {
        delete &ctrl;
    }

    contentControl() : control() {}
};