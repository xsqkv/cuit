// container control class file

#pragma once
#include<vector>

#include "control.hpp"


class contentControl : public control
{
    public:
    std::vector<control*> elements;

    void inline addControl(control& ctrl) noexcept
    {   
        ctrl.parent = this;
        elements.push_back(&ctrl);
    }

    void inline removeControl(control& ctrl) noexcept
    {
        delete &ctrl;
    }

    inline size_t Controls() noexcept
    {
        return elements.size();
    }

    contentControl() : control() {}
};