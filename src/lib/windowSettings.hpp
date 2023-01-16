// window settings class file

#pragma once

class windowSettings
{
    public:
    enum class windowStyles : uint8_t
    {
        SOLID,
        BORDERED,
        BORDERED_CORNERED,
        RECT,
        SMOOTH,
    };
    
    char8_t fill;

    char8_t borders;

    char8_t corners;

    char8_t hBar;
    char8_t vBar;

    char8_t topBar;
    char8_t leftBar;
    char8_t rightBar;
    char8_t downBar;

    char8_t leftTopCorner;
    char8_t rightTopCorner;
    char8_t leftDownCorner;
    char8_t rightDownCorner;

    windowSettings()
    {

    }
};