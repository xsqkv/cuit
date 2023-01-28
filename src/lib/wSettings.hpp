// window settings class file

#pragma once

class wSettings
{
    public:
    
    char fill;

    char topBar;
    char leftBar;
    char rightBar;
    char downBar;

    char leftTopCorner;
    char rightTopCorner;
    char leftDownCorner;
    char rightDownCorner;

    void setCorners(char chr)
    {
        leftTopCorner = chr;
        rightTopCorner = chr;
        leftDownCorner = chr;
        rightDownCorner = chr;
    }

    void setUpCorners(char chr)
    {
        leftTopCorner = chr;
        rightTopCorner = chr;
    }

    void setDownCorners(char chr)
    {
        leftDownCorner = chr;
        rightDownCorner = chr;
    }

    void setLeftCorners(char chr)
    {
        leftTopCorner = chr;
        leftDownCorner = chr;
    }

    void setRightCorners(char chr)
    {
        rightTopCorner = chr;
        rightDownCorner = chr;
    }

    void setBars(char chr)
    {
        topBar = chr;
        leftBar = chr;
        rightBar = chr;
        downBar = chr;
    }

    void setVBars(char chr)
    {
        leftBar = chr;
        rightBar = chr;
    }

    void setHBars(char chr)
    {
        topBar = chr;
        downBar = chr;
    }

    // default constructor
    wSettings() :
    fill('#'),
    topBar(0),
    leftBar(0),
    rightBar(0),
    downBar(0),
    leftTopCorner(0),
    rightTopCorner(0),
    leftDownCorner(0),
    rightDownCorner(0)
    {}
};