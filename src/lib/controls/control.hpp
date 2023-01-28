// control class file

#pragma once

#include "../sz.hpp"
#include "../pos.hpp"
#include "../cli.hpp"


class control
{
    public:
    bool topMost;
    bool focusable;
    bool focused;

    bool visible = 1;
    bool enabled;
    bool sizable;
    sz size;
    pos position;
    control* parent;
    
    virtual void draw() {}

    void setPos(pos _pos)
    {
        position = _pos;
        cli::clear();
        if(visible)draw();
    }

    void setSize(sz s)
    {
        size = s;
        cli::clear();
        if(visible) draw();
    }

    control() 
    {
        // Set global console buffer parent of all controls
        
        // auto w= cli::getSize();
        // parent->size  = {w.ws_col,w.ws_row};
        // parent->position = {0,0,0};
    }
};