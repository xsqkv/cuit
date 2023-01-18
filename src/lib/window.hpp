// window container control class file

#pragma once

#include<iostream>

#include "containerControl.hpp"
#include "wSettings.hpp"


class window : public containerControl
{
    protected:
    bool topMost;
    bool hasTitle;
    std::string title;

    public:

    wSettings settings;

    void draw() override
    {
        std::string win;

        // if fill variable not null draw rect
        if( settings.fill
            && !settings.leftTopCorner
            && !settings.topBar
            && !settings.rightTopCorner
            && !settings.leftBar
            && !settings.rightBar
            && !settings.leftDownCorner
            && !settings.downBar
            && !settings.rightDownCorner)
            {
                rect::drawRect(
                position.x,
                position.y,
                size.width,
                size.height,
                settings.fill
                );

                return;
            }

        //draw left top corner
        if(settings.leftTopCorner) win += settings.leftTopCorner;
        else win += settings.fill;

        //draw top bar
        if(settings.topBar) win += std::string(this->size.width - 2, settings.topBar);
        else win += std::string(this->size.width - 2, settings.fill);

        //draw right top corner
        if(settings.rightTopCorner) win += settings.rightTopCorner;
        else win += settings.fill;
        win += "\e[1B\e["+std::to_string(size.width)+"D";

        //draw left bar, fill, right bar.
        for(int i = 1; i < this->size.height-1; ++i)
        {
            //draw left bar
            if(settings.leftBar) win += settings.leftBar;
            else win += settings.fill;
            
            //draw fill
            win += std::string(this->size.width - 2, settings.fill);

            //draw right bar
            if(settings.rightBar) win += settings.rightBar;
            else win += settings.fill;
            win += "\e[1B\e["+std::to_string(size.width)+"D";
        }

        //draw left down corner
        if(settings.leftDownCorner) win += settings.leftDownCorner;
        else win += settings.fill;

        //draw down bar
        if(settings.downBar) win += std::string(this->size.width - 2, settings.downBar);
        else win += std::string(this->size.width - 2, settings.fill);

        //draw right down corner
        if(settings.rightDownCorner) win += settings.rightDownCorner;
        else win += settings.fill;

        // write whole window in console
        cli::setText(this->position.x, this->position.y, win);
    }

    void hide()
    {
        visible = 0; // set hidden flag
        cli::clear(); // clear all term buff
    }

    void show()
    {
        visible = 1;
        draw();
        for(auto& ctrl : elements) { ctrl->draw(); }
    }

    window() : containerControl() 
    {
        //elements.push_back();
    }

    window(unsigned width, unsigned height,bool normed=0) : window()
    {
        size = sz(width,height,normed);
        draw();
    }

    window(unsigned width, unsigned height, bool size_normed, unsigned pos_x, unsigned pos_y, bool pos_normed) : window()
    {
        size = sz(width,height,size_normed);
        position = pos(pos_x,pos_y,pos_normed);
    }

    window(sz SIZE) : window()
    {
        size = SIZE;
    }

    window(sz SIZE, pos POSITION) : window()
    {
        size = SIZE;
        position = POSITION;
    }
};
