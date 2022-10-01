#pragma once

#include<iostream>

#include "containerControl.h"
#include "windowSettings.h"


class window : public containerControl
{
    protected:
    bool topMost;
    bool hasTitle;
    std::string title;

    public:
    windowSettings settings;
    void draw() override
    {
        //position of start window x
        unsigned lx = this->position.x;
        //position of start window y
        unsigned ly = this->position.y;

        //position of end of window x
        unsigned fx = lx+this->size.width;
        //position of end of window y
        unsigned fy = ly+this->size.height;

        std::string cur = "";

        if(settings.fill && settings.topBar && settings.leftBar && settings.rightBar && settings.downBar && settings.leftTopCorner && settings.rightTopCorner && settings.leftDownCorner && settings.rightDownCorner)
        {
            cli::setChar(lx, ly, settings.leftTopCorner);
            cli::setChar(fx, ly, settings.rightTopCorner);
            cli::setChar(lx, fy, settings.leftDownCorner);
            cli::setChar(fx, fy, settings.rightDownCorner);
            for(unsigned y = ly+1; y < fy; y++)
            {
                for(unsigned x = lx+1; x < fx; x++)
                {
                    cli::setChar(x, y, settings.fill);
                }
            }
            std::cout << "\e[m";
            for(unsigned x=lx+1;x<fx;x++)cli::setChar(x,ly,settings.topBar);
            for(unsigned y=ly+1;y<fy;y++)cli::setChar(lx,y,settings.leftBar);
            for(unsigned x=lx+1;x<fx;x++)cli::setChar(x,fy,settings.downBar);
            for(unsigned y=ly+1;y<fy;y++)cli::setChar(fx,y,settings.rightBar);

            return;
        }   
        else if(settings.fill && settings.hBar && settings.vBar && settings.leftTopCorner && settings.rightTopCorner && settings.leftDownCorner && settings.rightDownCorner)
        {
            for(unsigned y = ly; y <= fy; y++)
            {
                for(unsigned x = lx; x <= fx; x++)
                {
                    if((y == ly || y == fy) && (x != lx && x != fx))//draw horisontal bars
                    {
                        cli::setChar(x, y, settings.hBar);
                    }
                    else if((y != ly && y != fy) && (x == lx || x == fx))//draw vertical bars
                    {
                        cli::setChar(x, y, settings.vBar);
                    }
                    else//draw 
                    {
                        cli::setChar(x, y, settings.fill);
                    }
                }
            }
            cli::setChar(lx, ly, settings.leftTopCorner);
            cli::setChar(fx, ly, settings.rightTopCorner);
            cli::setChar(lx, fy, settings.leftDownCorner);
            cli::setChar(fx, fy, settings.rightDownCorner);
            return;
        }
        else if(settings.fill && settings.borders && settings.leftTopCorner && settings.rightTopCorner && settings.leftDownCorner && settings.rightDownCorner)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    if(x==lx||x==fx||y==ly||y==fy) {cli::setChar(x,y,settings.borders); continue;}
                    cli::setChar(x,y,settings.fill);
                }
            }
            cli::setChar(lx, ly, settings.leftTopCorner);
            cli::setChar(fx, ly, settings.rightTopCorner);
            cli::setChar(lx, fy, settings.leftDownCorner);
            cli::setChar(fx, fy, settings.rightDownCorner);
            return;
        }
        else if(settings.fill && settings.corners && settings.topBar && settings.leftBar && settings.rightBar && settings.downBar)
        {
            cli::setChar(lx, ly, settings.corners);
            cli::setChar(fx, ly, settings.corners);
            cli::setChar(lx, fy, settings.corners);
            cli::setChar(fx, fy, settings.corners);
            for(unsigned y = ly+1; y < fy; y++)
            {
                for(unsigned x = lx+1; x < fx; x++)
                {
                    cli::setChar(x, y, settings.fill);
                }
            }
            
            for(unsigned x=lx+1;x<fx;x++)cli::setChar(x,ly,settings.topBar);
            for(unsigned y=ly+1;y<fy;y++)cli::setChar(lx,y,settings.leftBar);
            for(unsigned x=lx+1;x<fx;x++)cli::setChar(x,fy,settings.downBar);
            for(unsigned y=ly+1;y<fy;y++)cli::setChar(fx,y,settings.rightBar);

            return;
        }
        else if(settings.fill && settings.corners && settings.hBar && settings.vBar)
        {
            for(unsigned y = ly; y <= fy; y++)
            {
                for(unsigned x = lx; x <= fx; x++)
                {
                    if((y == ly || y == fy) && (x != lx && x != fx))//draw horisontal bars
                    {
                        cli::setChar(x, y, settings.hBar);
                    }
                    else if((y != ly && y != fy) && (x == lx || x == fx))//draw vertical bars
                    {
                        cli::setChar(x, y, settings.vBar);
                    }
                    else//draw 
                    {
                        cli::setChar(x, y, settings.fill);
                    }
                }
            }
            cli::setChar(lx, ly, settings.corners);
            cli::setChar(fx, ly, settings.corners);
            cli::setChar(lx, fy, settings.corners);
            cli::setChar(fx, fy, settings.corners);
            return;
        }
        else if(settings.fill && settings.corners && settings.borders)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    if(x==lx||x==fx||y==ly||y==fy) {cli::setChar(x,y,settings.borders); continue;}
                    cli::setChar(x,y,settings.fill);
                }
            }
            cli::setChar(lx, ly, settings.corners);
            cli::setChar(fx, ly, settings.corners);
            cli::setChar(lx, fy, settings.corners);
            cli::setChar(fx, fy, settings.corners);
            return;
        }
        else if(settings.fill && settings.leftTopCorner && settings.rightTopCorner && settings.leftDownCorner && settings.rightDownCorner)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    cli::setChar(x,y,settings.fill);
                }
            }
            cli::setChar(lx, ly, settings.leftTopCorner);
            cli::setChar(fx, ly, settings.rightTopCorner);
            cli::setChar(lx, fy, settings.leftDownCorner);
            cli::setChar(fx, fy, settings.rightDownCorner);
            return;
        }
        else if(settings.fill && settings.corners)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    cli::setChar(x,y,settings.fill);
                }
            }
            cli::setChar(lx, ly, settings.corners);
            cli::setChar(fx, ly, settings.corners);
            cli::setChar(lx, fy, settings.corners);
            cli::setChar(fx, fy, settings.corners);
            return;
        }
        else if(settings.fill && settings.topBar && settings.leftBar && settings.rightBar && settings.downBar)
        {
            for(unsigned y = ly+1; y < fy; y++)
            {
                for(unsigned x = lx+1; x < fx; x++)
                {
                    cli::setChar(x, y, settings.fill);
                }
            }
            
            for(unsigned x=lx+1;x<fx;x++)cli::setChar(x,ly,settings.topBar);
            for(unsigned y=ly+1;y<fy;y++)cli::setChar(lx,y,settings.leftBar);
            for(unsigned x=lx+1;x<fx;x++)cli::setChar(x,fy,settings.downBar);
            for(unsigned y=ly+1;y<fy;y++)cli::setChar(fx,y,settings.rightBar);

            return;
        }
        else if(settings.fill && settings.borders)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    if(x==lx||x==fx||y==ly||y==fy) {cli::setChar(x,y,settings.borders); continue;}
                    cli::setChar(x,y,settings.fill);
                }
            }
            return;
        }
        else if(settings.fill)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    cli::setChar(x,y,settings.fill);
                }
            }
            return;
        } 
        else
        {
            std::cout<<"format error"<<"\n";
        }
        
        std::cout << "\e[m"; //Reset color
    }

    void hide()
    {
        visible = 0;
        cli::clear();
    }

    void show()
    {
        visible = 1;
        draw();
        int controls = elements.getSize();
        for(int i=0;i < controls;i++)
        {
            elements.get(i)->draw();//call base class method
        }
    }

    window() : containerControl() 
    {
        elements.parent = this;
    }

    window(unsigned width, unsigned height,bool normed=0) : window()
    {
        size = sz(width,height,normed);
        draw();
    }
};
