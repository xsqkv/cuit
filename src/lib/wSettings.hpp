// window settings class file

#pragma once

class wSettings
{
    public:
    
    char fill{'#'};

    char topBar{'#'};
    char leftBar{'#'};
    char rightBar{'#'};
    char downBar{'#'};

    char leftTopCorner{'#'};
    char rightTopCorner{'#'};
    char leftDownCorner{'#'};
    char rightDownCorner{'#'};

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

    void setAll(char chr)
    {
        fill = chr;
        topBar = chr;
        leftBar = chr;
        rightBar = chr;
        downBar = chr;
        leftTopCorner = chr;
        rightTopCorner = chr;
        leftDownCorner = chr;
        rightDownCorner = chr;
    }

    // default constructor
    wSettings() {}
};