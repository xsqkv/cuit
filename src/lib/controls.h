#pragma once

#include<iostream>

#include "control.h"



class controls
{ 
    size_t size = 0;
    control** ctrls = NULL;
    public:
    control* parent;

    void add(control *ctrl)
    {
        ctrl->parent = this->parent;
        control** new_arr = new control*[size+1];
        for(int i=0;i<size;i++)
        {
            new_arr[i] = ctrls[i];
        }
        new_arr[size] = ctrl;
        int bytes = (++size)*sizeof(control**);
        ctrls = (control**)malloc(bytes);
        for(int i=0;i<size;i++)
        {
            ctrls[i] = new_arr[i];
        }
    }

    void remove(int idx)
    {
        control** new_arr = new control*[size-1];
        for(int i=0;i<size;i++)
        {
            if(i!=idx)
            {
                new_arr[i] = ctrls[i];
            }
        }
        int bytes = (--size)*sizeof(control**);
        ctrls = (control**)malloc(bytes);
        for(int i=0;i<size;i++)
        {
            ctrls[i] = new_arr[i];
        }
    }

    control* get(int idx)
    {
        return ctrls[idx];
    }

    size_t getSize()
    {
        return size;
    }

    controls(){}
};
