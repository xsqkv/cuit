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