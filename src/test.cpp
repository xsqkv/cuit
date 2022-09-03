#include <iostream>
#include <sys/ioctl.h> // ioctl // TIOCGWINSZ
#include <unistd.h> //STDOUT_FILENO in cli::getSize()

#include "hsv.h"
#include "utils.h"

// ======== CUI =========
// Global Settings
bool EXTENDED_COLORS = 1;
bool PSEUDO_GRAPHICS = 1;
bool CUSTOM_FONT = 0;
bool USE_SCALING = 0;



class hsl
{
    public:
    double h;
    double s;
    double l;

    inline constexpr void print()
    {
        printf("%3.1f %3.1f%% %3.1f%% \n",h,s,l);
    }

    inline constexpr void fromHSV(hsv& x)
    {
        h = x.h;
        l = x.v * (1 - x.v / 2);
        if(l == 0 || l == 1) s = 0;
        else (x.v - l) / min(l, 1 - l);
    }

    inline constexpr void toHSV(hsv& x)
    {
        double hh = h;
        double ss = s / 100;
        double ll = l / 100;

        x.h = hh;
        hh *= 2;
        if(ll <= 1) ss *= ll;
        else ss *= 2 - ll;
        x.v = (ll + ss) / 2;
        x.s = (2*ss) / (ll + ss);

        x.s = round(x.s * 100.0);
        x.v = round(x.v * 100.0);
    }

    inline constexpr hsl() : h(0), s(0), l(0) {}

    inline constexpr hsl(double H,double S,double L)
    {
        h=H;
        s=S;
        l=L;
    }
};

class rgb
{
    public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    float pr;
    float pg;
    float pb;
    
    inline constexpr void print()
    {
        printf("%d %d %d \n",r,g,b);
    }

    inline constexpr void countPercents()
    {
        pr = r / 255.0;
        pg = g / 255.0;
        pb = b / 255.0;
    }

    inline constexpr void fromHSL(hsl& val)
    {
        float h = val.h;
        float s = val.s;
        float l = val.l;

        float c = (1 - abs(2 * l - 1)) - s;

        h /= 60;

        float x = c * (1 - abs(h));

        if(0 <= h && h < 1) { r=c;g=x;b=0; }
        else if(1 <= h && h < 2) { r=x;g=c;b=0; }
        else if(2 <= h && h < 3) { r=0;g=c;b=x; }
        else if(3 <= h && h < 4) { r=0;g=x;b=c; }
        else if(4 <= h && h < 5) { r=x;g=0;b=c; }
        else if(5 <= h && h < 6) { r=c;g=0;b=x; }

        float m = l - c / 2;

        r += m;
        g += m;
        b += m;

        countPercents();
    }

    inline constexpr void toHSL(hsl& x)
    {
        float R = pr;
        float G = pg;
        float B = pb;

        float mx = max(r,g,b);
        float mn = min(r,g,b);

        if(mx == mn) return;

        if(mx == R && G >= B) x.h = 60 * (G-B) / (mx - mn) + 0;
        else if(mx == R && G < B) x.h = 60 * (G-B) / (mx - mn) + 360;
        else if(mx == G) x.h = 60 * (B-R) / (mx - mn) + 120;
        else if(mx == B) x.h = 60 * (R-G) / (mx - mn) + 240;

        x.l = 0.5 * (mx + mn);

        x.s = (mx - mn) / (1 - abs(1 - (mx+mn)));
    }

    inline constexpr void fromHSV(hsv& val)
    {
        float h=val.h;
        float s=val.s;
        float v=val.v;

        h = abs(h / 60) % 6;

        float vm = ((100-s)*v) / 100;
        float a = (v - vm) * ((int)h % 60) / 60;
        float vi = vm + a;
        float vd = v - a;

        if(h == 0) { r=v;g=vi;b=vm; }
        else if(h == 1) { r=vd;g=v;b=vm; }
        else if(h == 2) { r=vm;g=v;b=vi; }
        else if(h == 3) { r=vm;g=vd;b=v; }
        else if(h == 4) { r=vi;g=vm;b=v; }
        else if(h == 5) { r=v;g=vm;b=vd; }

        countPercents();
    }

    inline constexpr void toHSV(hsv& x)
    {
        float R = pr;
        float G = pg;
        float B = pb;

        float mx = max(R,G,B);
        float mn = min(R,G,B);

        if(mx == mn)return;

        if(mx == R && G >= B) x.h = 60 * (G-B) / (mx - mn) + 0;
        else if(mx == R && G < B) x.h = 60 * (G-B) / (mx - mn) + 360;
        else if(mx == G) x.h = 60 * (B-R) / (mx - mn) + 120;
        else if(mx == B) x.h = 60 * (R-G) / (mx - mn) + 240;

        if(mx == 0) x.s = 0;
        else x.s = 1 - mx / mn;

        x.v = mx;
    }

    inline constexpr void fromHEX(char* hex)
    {
        int val = from16to10(hex);
        r = val >> 24;
        g = val >> 16;
        b = val >> 8;
    }

    inline constexpr rgb() : r(0),g(0),b(0) , pr(0),pg(0),pb(0) {}

    inline constexpr rgb(uint8_t red, uint8_t green, uint8_t blue)
    {
        r=red;
        g=green;
        b=blue;

        countPercents();
    }

    inline constexpr rgb(char* hex)
    {
        fromHEX(hex);
    }
};

class sz
{
    public:
    unsigned width;
    unsigned height;
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    public:
    sz(){}

    sz(unsigned w, unsigned h, bool normed = 0)
    {
        if(normed) w *= norm;
        width = w;
        height = h;
    }
};

class pos
{
    float fx,fy;
    public:
    unsigned x,y;
    
    enum place : char8_t
    {
         TOP_LEFT,      TOP_CENTER,      TOP_RIGHT,




        MIDDLE_LEFT,      CENTER,       MIDDLE_RIGHT,




        BOTTOM_LEFT,   BOTTOM_CENTER,   BOTTOM_RIGHT
    };
    
    static constexpr float norm = 79.0/34.0; // pixel on pixel division

    pos(){}

    pos(unsigned X, unsigned Y, bool normed = 0)
    {
        //if(!x)x=1;
        //if(!y)y=1;
        if(normed) x *= norm;

        x=X;
        y=Y;
    }

    pos(float x, float y, unsigned width, unsigned height, bool normed = 0) : pos(static_cast<int>(width*x),static_cast<int>(height*y),normed) {}
    
    pos(float x, float y, sz size, bool normed = 0)  : pos(static_cast<int>(size.width*x),static_cast<int>(size.height*y),normed) {}
};

class cchar
{
    protected:
    std::string clr;
    std::string str;
    
    public:
    enum class style : char8_t
    {
        Bold = 1,
        Low_Intensity = 2,
        Italic = 4,
        Underline =8,
        Blinking=16,
        Reverse=32,
        Background=64,
        Invisible=128
    };
    enum class sysColors : char8_t
    {
        Black,
        Maroon,
        Green,
        Olive,
        Navy,
        Purple,
        Teal,
        Silver,
        Grey,
        Red,
        Lime,
        Yellow,
        Blue,
        Fuchsia,
        Aqua,
        White
    };
    enum class exColors : char8_t
    {
        Grey0 = 16,
        NavyBlue,
        DarkBlue,
        Blue3,
        Blue4,
        Blue1,
        DarkGreen,
        DeepSkyBlue4,
        DeepSkyBlue5,
        DeepSkyBlue6,
        DodgerBlue3,
        DodgerBlue2,
        Green4,
        SpringGreen4,
        Turquoise4,
        DeepSkyBlue3,
        DeepSkyBlue0,
        DodgerBlue1,
        Green3,
        SpringGreen3,
        DarkCyan,
        LightSeaGreen,
        DeepSkyBlue2,
        DeepSkyBlue1,
        Green2,
        SpringGreen6,
        SpringGreen5,
        Cyan3,
        DarkTurquoise,
        Turquoise2,
        Green1,
        SpringGreen2,
        SpringGreen1,
        MediumSpringGreen,
        Cyan2,
        Cyan1,
        DarkRed,
        DeepPink4,
        Purple4,
        Purple3,
        Purple2,
        BlueViolet,
        Orange4,
        Grey37,
        MediumPurple4,
        SlateBlue3,
        SlateBlue2,
        RoyalBlue1,
        Chartreuse4,
        DarkSeaGreen,
        PaleTurquoise4,
        SteelBlue,
        SteelBlue3,
        CornflowerBlue,
        Chartreuse3,
        DarkSeaGreen6,
        CadetBlue,
        CadetBlue1,
        SkyBlue3,
        SteelBlue1,
        Chartreuse2,
        PaleGreen3,
        SeaGreen3,
        Aquamarine3,
        MediumTurquoise,
        SteelBlue0,
        Chartreuse1,
        SeaGreen2,
        SeaGreen1,
        SeaGreen0,
        Aquamarine1,
        DarkSlateGray2,
        DarkRed0,
        DeepPink3,
        DarkMagenta,
        DarkMagenta1,
        DarkViolet,
        Purple01,
        Orange3,
        LightPink4,
        Plum4,
        MediumPurple3,
        MediumPurple2,
        SlateBlue1,
        Yellow6,
        Wheat4,
        Grey53,
        LightSlateGrey,
        MediumPurple,
        LightSlateBlue,
        Yellow3,
        DarkOliveGreen3,
        DarkSeaGreen5,
        LightSkyBlue3,
        LightSkyBlue4,
        SkyBlue2,
        Chartreuse0,
        DarkOliveGreen2,
        PaleGreen4,
        DarkSeaGreen2,
        DarkSlateGray3,
        SkyBlue1,
        Chartreuse,
        LightGreen,
        LightGreen1,
        PaleGreen1,
        Aquamarine0,
        DarkSlateGray1,
        Red3,
        DeepPink2,
        MediumVioletRed,
        Magenta5,
        DarkViolet0,
        Purple0,
        DarkOrange3,
        IndianRed,
        HotPink3,
        MediumOrchid5,
        MediumOrchid,
        MediumPurple0,
        DarkGoldenrod,
        LightSalmon3,
        RosyBrown,
        Grey63,
        MediumPurple5,
        MediumPurple1,
        Gold3,
        DarkKhaki,
        NavajoWhite3,
        Grey69,
        LightSteelBlue3,
        LightSteelBlue,
        Yellow2,
        DarkOliveGreen1,
        DarkSeaGreen4,
        DarkSeaGreen3,
        LightCyan3,
        LightSkyBlue1,
        GreenYellow,
        DarkOliveGreen00,
        PaleGreen2,
        DarkSeaGreen01,
        DarkSeaGreen1,
        PaleTurquoise1,
        Red2,
        DeepPink0,
        DeepPink1,
        Magenta0,
        Magenta2,
        Magenta1,
        DarkOrange2,
        IndianRed1,
        HotPink1,
        HotPink2,
        Orchid,
        MediumOrchid1,
        Orange2,
        LightSalmon0,
        LightPink3,
        Pink3,
        Plum3,
        Violet,
        Gold2,
        LightGoldenrod3,
        Tan,
        MistyRose3,
        Thistle3,
        Plum2,
        Yellow1,
        Khaki3,
        LightGoldenrod4,
        LightYellow3,
        Grey84,
        LightSteelBlue1,
        Yellow4,
        DarkOliveGreen,
        DarkOliveGreen0,
        DarkSeaGreen0,
        Honeydew2,
        LightCyan1,
        Red1,
        DeepPink02,
        DeepPink,
        DeepPink01,
        Magenta3,
        Magenta4,
        OrangeRed2,
        IndianRed4,
        IndianRed0,
        HotPink,
        HotPink4,
        MediumOrchid3,
        DarkOrange,
        Salmon1,
        LightCoral,
        PaleVioletRed1,
        Orchid2,
        Orchid1,
        Orange0,
        SandyBrown,
        LightSalmon1,
        LightPink1,
        Pink1,
        Plum1,
        Gold1,
        LightGoldenrod2,
        LightGoldenrod0,
        NavajoWhite5,
        MistyRose1,
        Thistle1,
        Yellow5,
        LightGoldenrod1,
        Khaki1,
        Wheat1,
        Cornsilk1
    };
    enum class bwColors : char8_t
    {
        Grey100 = 231U,
        Grey3,
        Grey7,
        Grey11,
        Grey15,
        Grey19,
        Grey23,
        Grey27,
        Grey30,
        Grey35,
        Grey39,
        Grey42,
        Grey46,
        Grey50,
        Grey54,
        Grey58,
        Grey62,
        Grey66,
        Grey70,
        Grey74,
        Grey78,
        Grey82,
        Grey85,
        Grey89,
        Grey93
    };

    void setColor(unsigned foreground, unsigned background, unsigned style)
    {
        std::string result = "\e[";
        if(style)
        {   
            if(style & 1)result += "01;";
            if(style & 2)result += "02;";
            if(style & 4)result += "03;";
            if(style & 8)result += "04;";
            if(style & 16)result += "05;";
            if(style & 32)result += "06;";
            if(style & 64)result += "07;";
            if(style & 128)result += "08;";
        }  
        result += "38;05;" + its(foreground) + ";";
        result += "48;05;" + its(background) + "m";
        clr = result;
    }

    char* getStr()
    {
        return (char*)(str.c_str());
    }

    char* getClr()
    {
        return (char*)(clr.c_str());
    }

    operator bool() const
    {
        return strlen((char*)str.c_str());
    }

    cchar() : clr(""), str("") {}

    cchar(char ch,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.push_back(ch);
        setColor(foreground,background,style);
    }

    cchar(char* s,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.assign(s);
        setColor(foreground,background,style);
    }

    cchar(const char* s,unsigned foreground=0, unsigned background=0, unsigned style=0)
    {
        str.assign(s);
        setColor(foreground,background,style);
    }

    cchar(unsigned foreground, unsigned background, unsigned style)
    {
        setColor(foreground,background,style);
    }
};

class pseudoGraphics
{
    public:
    enum Single : char8_t
    {
        SINGLE_HORISONTAL,
        SINGLE_VERTICAL,
        SINGLE_TRIPPLE_LEFT,
        SINGLE_TRIPPLE_RIGHT,
        SINGLE_TRIPPLE_UP,
        SINGLE_TRIPPLE_DOWN,
        SINGLE_LEFT_DOWN_CORNER,
        SINGLE_LEFT_UP_CORNER,
        SINGLE_RIGHT_DOWN_CORNER,
        SINGLE_RIGHT_UP_CORNER,
        SINGLE_CROSS,
        SINGLE_LEFT_UP_SMOOTH_CORNER,
        SINGLE_RIGHT_UP_SMOOTH_CORNER,
        SINGLE_RIGHT_DOWN_SMOOTH_CORNER,
        SINGLE_LEFT_DOWN_SMOOTH_CORNER,
    };
    const char* single[15] = {
        "─",
        "│",
        "┤",
        "├",
        "┴",
        "┬",
        "└",
        "┌",
        "┘",
        "┐",
        "┼",
        "╭",
        "╮",
        "╯",
        "╰",
    };

    enum SingleDoubled : char8_t
    {
        SINGLE_DOUBLED_HORISONTAL,
        SINGLE_DOUBLED_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_LEFT_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_LEFT_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_RIGHT_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_RIGHT_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_UP_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_UP_VERTICAL,
        SINGLE_DOUBLED_TRIPPLE_DOWN_HORISONTAL,
        SINGLE_DOUBLED_TRIPPLE_DOWN_VERTICAL,
        SINGLE_DOUBLED_LEFT_DOWN_CORNER_HORISONTAL,
        SINGLE_DOUBLED_LEFT_DOWN_CORNER_VERTICAL,
        SINGLE_DOUBLED_LEFT_UP_CORNER_HORISONTAL,
        SINGLE_DOUBLED_LEFT_UP_CORNER_VERTICAL,
        SINGLE_DOUBLED_RIGHT_DOWN_CORNER_HORISONTAL,
        SINGLE_DOUBLED_RIGHT_DOWN_CORNER_VERTICAL,
        SINGLE_DOUBLED_RIGHT_UP_CORNER_HORISONTAL,
        SINGLE_DOUBLED_RIGHT_UP_CORNER_VERTICAL,
        SINGLE_DOUBLED_CROSS_HORISONTAL,
        SINGLE_DOUBLED_CROSS_VERTICAL,
    };
    const char* singleDoubled[20] = {
        "═",
        "║",
        "╡",
        "╢",
        "╞",
        "╟",
        "╧",
        "╨",
        "╤",
        "╥",
        "╘",
        "╙",
        "╒",
        "╓",
        "╛",
        "╜",
        "╕",
        "╖",
        "╪",
        "╫",
    };

    enum Doubled : char8_t
    {
        DOUBLED_HORISONTAL,
        DOUBLED_VERTICAL,
        DOUBLED_TRIPPLE_LEFT,
        DOUBLED_TRIPPLE_RIGHT,
        DOUBLED_TRIPPLE_UP,
        DOUBLED_TRIPPLE_DOWN,
        DOUBLED_LEFT_DOWN_CORNER,
        DOUBLED_LEFT_UP_CORNER,
        DOUBLED_RIGHT_DOWN_CORNER,
        DOUBLED_RIGHT_UP_CORNER,
        DOUBLED_CROSS,
    };
    const char* doubled[11] = {
        "═",
        "║",
        "╣",
        "╠",
        "╩",
        "╦",
        "╚",
        "╔",
        "╝",
        "╗",
        "╬",
    };

    enum Bold : char8_t
    {
        BOLD_HORISONTAL,
        BOLD_VERTICAL,
        BOLD_TRIPPLE_LEFT,
        BOLD_TRIPPLE_RIGHT,
        BOLD_TRIPPLE_UP,
        BOLD_TRIPPLE_DOWN,
        BOLD_LEFT_DOWN_CORNER,
        BOLD_LEFT_UP_CORNER,
        BOLD_RIGHT_DOWN_CORNER,
        BOLD_RIGHT_UP_CORNER,
        BOLD_CROSS,
    };
    const char* bold[11] = {
        "━",
        "┃",
        "┫",
        "┣",
        "┻",
        "┳",
        "┗",
        "┏",
        "┛",
        "┓",
        "╋",
    };

    enum SlimBolded : char8_t
    {
        RIGHT_SLIM_BOLDED_LINE,
        DOWN_SLIM_BOLDED_LINE,
        LEFT_SLIM_BOLDED_LINE,
        UP_SLIM_BOLDED_LINE,
        SAMPLE,
    };
    const char* slimBolded[50] = {
        "╼",
        "╽",
        "╾",
        "╿",
        "┍",
        "┎",
        "┑",
        "┒",
        "┕",
        "┖",
        "┙",
        "┚",
        "┝",
        "┞",
        "┟",
        "┠",
        "┡",
        "┢",
        "┥",
        "┦",
        "┧",
        "┨",
        "┩",
        "┪",
        "┭",
        "┮",
        "┯",
        "┰",
        "┱",
        "┲",
        "┵",
        "┶",
        "┷",
        "┸",
        "┹",
        "┺",
        "┽",
        "┾",
        "┿",
        "╀",
        "╁",
        "╂",
        "╃",
        "╄",
        "╅",
        "╆",
        "╇",
        "╈",
        "╉",
        "╊",
    };

    enum PiecesLines : char8_t
    {
        LEFT_PIECE_INE,
        UP_PIECE_LINE,
        RIGHT_PIECE_LINE,
        DOWN_PIECE_LINE,
    };
    const char* piecesLines[4] = {
        "╴",
        "╵",
        "╶",
        "╷",
    };

    enum BoldPieces : char8_t
    {
        LEFT_PIECE_BOLD_LINE,
        UP_PIECE_BOLD_LINE,
        RIGHT_PIECE_BOLD_LINE,
        DOWN_PIECE_BOLD_LINE,
    };
    const char* boldPieces[4] = {
        "╸",
        "╹",
        "╺",
        "╻",
    };

    enum DottedLines : char8_t
    {
        HORISONTAL_LOW_DOTTED_LINE,
        VERTICAL_LOW_DOTTED_LINE,
        HORISONTAL_MED_DOTTED_LINE,
        VERTICAL_MED_DOTTED_LINE,
        HORISONTAL_HIGH_DOTTED_LINE,
        VERTICAL_HIGH_DOTTED_LINE,
    };
    const char* dottedLines[6] = {
        "╌",
        "╎",
        "┄",
        "┆",
        "┈",
        "┊",
    };

    enum BoldDottedLines : char8_t
    {
        HORISONTAL_LOW_BOLD_DOTTED_LINE,
        VERTICAL_LOW_BOLD_DOTTED_LINE,
        HORISONTAL_MED_BOLD_DOTTED_LINE,
        VERTICAL_MED_BOLD_DOTTED_LINE,
        HORISONTAL_HIGH_BOLD_DOTTED_LINE,
        VERTICAL_HIGH_BOLD_DOTTED_LINE,
    };
    const char* boldDottedLines[6] = {
        "╍",
        "╏",
        "┅",
        "┇",
        "┉",
        "┉",
    };

    enum DiagonaleLines : char8_t
    {
        DIAGONALE_LINE,
        BACK_DIAGONALE_LINE,
        DOUBLE_DIAGONALE_LINE,
    };
    const char* diagonaleLines[3] = {
        "╱",
        "╲",
        "╳",
    };

    enum Blocks : char8_t
    {
        LOW_LIGHT_BLOCK,
        MID_LIGHT_BLOCK,
        HIGH_LIGHT_BLOCK,
        LIGHT_BLOCK,
        DOWN_HALF_BLOCK,
        UP_HALF_BLOCK,
        LEFT_HALF_BLOCK,
        RIGHT_HALF_BLOCK,
        SQUARE,
        LOW_RECTANGLE
    };
    const char* blocks[10] = {
        "░",
        "▒",
        "▓",
        "█",
        "▄",
        "▀",
        "▌",
        "▐",
        "■",
        "▬"
    };

    enum Etc : char8_t
    {
        SMILE,
        FILLED_SMILE,
        HEART,
        CLUB,
        DIAMOND,
        SPADE,
        SMALL_FILLED_CIRCLE,
        SQUARED_CIRCLE,
        CIRCLE,
        FILLED_SQUARED_CIRCLE,
        MALE,
        FEMALE,
        EIGHT_NOTE,
        TWO_EIGHT_NOTE,
        SUN,
        RIGHT_ARROW,
        LEFT_ARROW,
        UP_ARROW,
        DOWN_ARROW,
        DOUBLE_SCREAMER,
        PILCROW,
        PARAGRAPH,
        SMALL_ARROW_UP,
        SMALL_ARROW_DOWN,
        SMALL_ARROW_RIGHT,
        SMALL_ARROW_LEFT,
        UP_DOWN_ARROW_LINE,
        UP_DOWN_ARROW,
        LEFT_RIGHT_ARROW,
        THREE_DOTS,
        CHRIST,
        DOUBLE_CHRIST,
        HORISONTAL_LINE,
        LONG_HORISONTAL_LINE,
        TM,
        LINED_CIRCLE,
        TWO_VERTICAL_LINES,
        C,
        TOP_RIGHT_CORNER,
        R,
        CELSIUS,
        PLUS_MINUS,
        FILLED_CIRCLE,
        BIG_FILLED_CIRCLE,
        BIG_BORDERED_FILLED_CIRCLE,
        WIDE_DIAMOND,
    };
    const char* etc[46] = {
        "☺",
        "☻",
        "♥",
        "♣",
        "♦",
        "♠",
        "•",
        "◘",
        "○",
        "◙",
        "♂",
        "♀",
        "♪",
        "♫",
        "☼",
        "►",
        "◄",
        "▲",
        "▼",
        "‼",
        "¶",
        "§",
        "↑",
        "↓",
        "→",
        "←",
        "↨",
        "↕",
        "↔",
        "…",
        "†",
        "‡",
        "–",
        "—",
        "™",
        "¤",
        "¦",
        "©",
        "¬",
        "®",
        "°",
        "±",
        "·",
        "●",
        "◉",
        "◆",
    };
};

class cli final
{
    public:
    bool cursorVisibility;
    int width;
    int height;

    winsize getSize()
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w;
    }

    sz getSz()
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return sz(w.ws_col,w.ws_row);
    }

    inline void clear()
    {
        std::cout << "\ec";
    }

    inline void hideCursor()
    {
        std::cout << "\e[?25l";
        cursorVisibility = 0;
    }

    inline void showCursor()
    {
        std::cout << "\e[?25h";
        cursorVisibility = 1;
    }

    inline void setCursor(unsigned x, unsigned y)
    {
        std::cout << "\e[" << y << ";" << x << "H";
    }

    inline void setChar(unsigned x, unsigned y, char* pchr)
    {
        std::cout << "\e[" << y << ";" << x << "H" << pchr;
    }

    inline void setChar(unsigned x, unsigned y, const char* pchr)
    {
        std::cout << "\e[" << y << ";" << x << "H" << pchr;
    }

    inline const void setChar(unsigned x, unsigned y, cchar pchr)
    {
        std::cout << "\e[" << y << ";" << x << "H" << pchr.getClr() << pchr.getStr();
    }

    inline const void setChar(unsigned x, unsigned y, std::string str)
    {
        std::cout << "\e[" << y << ";" << x << "H" << str.c_str();
    }

};

class control
{
    public:
    bool focusable;
    bool focused;
    bool visible=0;
    bool enabled;
    bool sizable;
    sz size;
    pos position;
    control* parent;
    
    virtual void draw()
    {

    }

    void setPos(pos _pos)
    {
        position = _pos;
        cli().clear();
        if(visible)draw();
    }

    void setSize(sz s)
    {
        size = s;
        cli().clear();
        if(visible)draw();
    }

    control() 
    {
        //parent->size = cli().getSz();
        //parent->position = {0,0};
    }
};

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

class scrollableControl : public control
{
    public:
    bool inactiveScrollBarsVisibility;
    bool scrollBarsVisibility;
    bool swipeSupport;
    char8_t scrollSpeed = 1;
};

class containerControl : public control
{
    public:
    controls elements;

    containerControl() : control() 
    {
        elements.parent = this->parent;
    }
};

class windowSettings
{
    public:
    enum class windowStyles : char8_t
    {
        SOLID,
        BORDERED,
        BORDERED_CORNERED,
        RECT,
        SMOOTH,
    };
    
    cchar fill{""};

    cchar borders{""};

    cchar corners{""};

    cchar hBar{""};
    cchar vBar{""};

    cchar topBar{""};
    cchar leftBar{""};
    cchar rightBar{""};
    cchar downBar{""};

    cchar leftTopCorner{""};
    cchar rightTopCorner{""};
    cchar leftDownCorner{""};
    cchar rightDownCorner{""};

    windowSettings()
    {

    }
};

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
            cli().setChar(lx, ly, settings.leftTopCorner);
            cli().setChar(fx, ly, settings.rightTopCorner);
            cli().setChar(lx, fy, settings.leftDownCorner);
            cli().setChar(fx, fy, settings.rightDownCorner);
            for(unsigned y = ly+1; y < fy; y++)
            {
                for(unsigned x = lx+1; x < fx; x++)
                {
                    cli().setChar(x, y, settings.fill);
                }
            }
            std::cout << "\e[m";
            for(unsigned x=lx+1;x<fx;x++)cli().setChar(x,ly,settings.topBar);
            for(unsigned y=ly+1;y<fy;y++)cli().setChar(lx,y,settings.leftBar);
            for(unsigned x=lx+1;x<fx;x++)cli().setChar(x,fy,settings.downBar);
            for(unsigned y=ly+1;y<fy;y++)cli().setChar(fx,y,settings.rightBar);

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
                        cli().setChar(x, y, settings.hBar);
                    }
                    else if((y != ly && y != fy) && (x == lx || x == fx))//draw vertical bars
                    {
                        cli().setChar(x, y, settings.vBar);
                    }
                    else//draw 
                    {
                        cli().setChar(x, y, settings.fill);
                    }
                }
            }
            cli().setChar(lx, ly, settings.leftTopCorner);
            cli().setChar(fx, ly, settings.rightTopCorner);
            cli().setChar(lx, fy, settings.leftDownCorner);
            cli().setChar(fx, fy, settings.rightDownCorner);
            return;
        }
        else if(settings.fill && settings.borders && settings.leftTopCorner && settings.rightTopCorner && settings.leftDownCorner && settings.rightDownCorner)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    if(x==lx||x==fx||y==ly||y==fy) {cli().setChar(x,y,settings.borders); continue;}
                    cli().setChar(x,y,settings.fill);
                }
            }
            cli().setChar(lx, ly, settings.leftTopCorner);
            cli().setChar(fx, ly, settings.rightTopCorner);
            cli().setChar(lx, fy, settings.leftDownCorner);
            cli().setChar(fx, fy, settings.rightDownCorner);
            return;
        }
        else if(settings.fill && settings.corners && settings.topBar && settings.leftBar && settings.rightBar && settings.downBar)
        {
            cli().setChar(lx, ly, settings.corners);
            cli().setChar(fx, ly, settings.corners);
            cli().setChar(lx, fy, settings.corners);
            cli().setChar(fx, fy, settings.corners);
            for(unsigned y = ly+1; y < fy; y++)
            {
                for(unsigned x = lx+1; x < fx; x++)
                {
                    cli().setChar(x, y, settings.fill);
                }
            }
            
            for(unsigned x=lx+1;x<fx;x++)cli().setChar(x,ly,settings.topBar);
            for(unsigned y=ly+1;y<fy;y++)cli().setChar(lx,y,settings.leftBar);
            for(unsigned x=lx+1;x<fx;x++)cli().setChar(x,fy,settings.downBar);
            for(unsigned y=ly+1;y<fy;y++)cli().setChar(fx,y,settings.rightBar);

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
                        cli().setChar(x, y, settings.hBar);
                    }
                    else if((y != ly && y != fy) && (x == lx || x == fx))//draw vertical bars
                    {
                        cli().setChar(x, y, settings.vBar);
                    }
                    else//draw 
                    {
                        cli().setChar(x, y, settings.fill);
                    }
                }
            }
            cli().setChar(lx, ly, settings.corners);
            cli().setChar(fx, ly, settings.corners);
            cli().setChar(lx, fy, settings.corners);
            cli().setChar(fx, fy, settings.corners);
            return;
        }
        else if(settings.fill && settings.corners && settings.borders)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    if(x==lx||x==fx||y==ly||y==fy) {cli().setChar(x,y,settings.borders); continue;}
                    cli().setChar(x,y,settings.fill);
                }
            }
            cli().setChar(lx, ly, settings.corners);
            cli().setChar(fx, ly, settings.corners);
            cli().setChar(lx, fy, settings.corners);
            cli().setChar(fx, fy, settings.corners);
            return;
        }
        else if(settings.fill && settings.leftTopCorner && settings.rightTopCorner && settings.leftDownCorner && settings.rightDownCorner)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    cli().setChar(x,y,settings.fill);
                }
            }
            cli().setChar(lx, ly, settings.leftTopCorner);
            cli().setChar(fx, ly, settings.rightTopCorner);
            cli().setChar(lx, fy, settings.leftDownCorner);
            cli().setChar(fx, fy, settings.rightDownCorner);
            return;
        }
        else if(settings.fill && settings.corners)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    cli().setChar(x,y,settings.fill);
                }
            }
            cli().setChar(lx, ly, settings.corners);
            cli().setChar(fx, ly, settings.corners);
            cli().setChar(lx, fy, settings.corners);
            cli().setChar(fx, fy, settings.corners);
            return;
        }
        else if(settings.fill && settings.topBar && settings.leftBar && settings.rightBar && settings.downBar)
        {
            for(unsigned y = ly+1; y < fy; y++)
            {
                for(unsigned x = lx+1; x < fx; x++)
                {
                    cli().setChar(x, y, settings.fill);
                }
            }
            
            for(unsigned x=lx+1;x<fx;x++)cli().setChar(x,ly,settings.topBar);
            for(unsigned y=ly+1;y<fy;y++)cli().setChar(lx,y,settings.leftBar);
            for(unsigned x=lx+1;x<fx;x++)cli().setChar(x,fy,settings.downBar);
            for(unsigned y=ly+1;y<fy;y++)cli().setChar(fx,y,settings.rightBar);

            return;
        }
        else if(settings.fill && settings.borders)
        {
            for(unsigned y=ly;y<=fy;y++)
            {
                for(unsigned x=lx;x<=fx;x++)
                {
                    if(x==lx||x==fx||y==ly||y==fy) {cli().setChar(x,y,settings.borders); continue;}
                    cli().setChar(x,y,settings.fill);
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
                    cli().setChar(x,y,settings.fill);
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
        cli().clear();
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

class label : public control
{
    cchar text;
    public:
    bool wrap = 0;// abo| -> abo|:ba |
    bool overwriteBorders = 1;//if 1 = abob / if 0 = abo|
    bool wordwrap = 0;// aboba| -> aboba|:boba |
    char8_t charwrap = 0;//if 0 - disabled / count of chars to wrap to new line
    
    void print()
    {
        int src = position.x;
        int dst = parent->size.width+overwriteBorders;
        if(src>dst)return;
        char* c = text.getStr();
        std::cout << text.getClr();
        while(src != dst)
        {
            std::cout << *c;
            c++;
            src++;
        }
    }

    void draw() override
    {
        cli().setCursor(this->parent->position.x+position.x,this->parent->position.y+position.y);
        print();
        std::cout << "\e[0m";//reset color
    }
    
    void setText(cchar str)
    {
        text = str;
        size = sz(strlen(text.getStr()),1);
    }

    label() {}

    label(cchar str)
    {
        text = str;
        size = sz(strlen(text.getStr()),1);
    }
};

class panel : public containerControl
{
    panel() {}
};

class button : public control
{
    enum class textAlign : char8_t
    {
        LEFT,
        CENTER,
        RIGHT
    };
};

namespace bt
{
    inline void st(short& num,uint8_t idx)
    {
        idx--;
        num |= 1 << idx;
    }

    inline void ust(short& num,uint8_t idx)
    {
        idx--;
        num &= ~(1<<idx);
    }

    inline bool get(short num,uint8_t idx)
    {
        idx--;
        return 1 << idx & num;
    }

    inline void prnt(short num)
    {
        std::string str("");
        for(int i = 0;i < sizeof(short);i++)
        {
            for(int j = 0;j < 8;j++)
            {
                str = its(num % 2) + str;
                num >>= 1;
            }
        }
        str += "\n";
        std::cerr<<str;
    }
}

void test()
{
    cli().clear();
    window w(5,5,1);
    w.setPos({5,5,1});
    w.settings.fill={"o",47};
    w.settings.borders={"*",123};
    w.settings.corners={"7",5};
    w.settings.hBar={"-",30};
    w.settings.vBar={"|",21};
    //w.settings.topBar={"<",134};
    //w.settings.leftBar={"v",200};
    //w.settings.rightBar={"^",250};
    //w.settings.downBar={">",150};
//
    //w.settings.leftTopCorner={"<",134};
    //w.settings.rightTopCorner={"^",250};
    //w.settings.leftDownCorner={"v",200};
    //w.settings.rightDownCorner={">",150};
    label l;
    l.overwriteBorders = 0;
    l.setPos({7,3,1});
    l.setText({"label",177});
    w.elements.add(&l);
    w.show();
    cli().setCursor(0,0);
}

inline constexpr void rgb2seq(uint8_t &x)
{
    if(x < 47)x=0;
    else if(x >= 47 && x < 115)x=1;
    else if(x >= 115 && x < 155)x=2;
    else if(x >= 155 && x < 195)x=3;
    else if(x >= 195 && x < 235)x=4;
    else x=5;
}

inline constexpr uint8_t get_seq(uint8_t r,uint8_t g,uint8_t b)
{
    rgb2seq(r);
    rgb2seq(g);
    rgb2seq(b);
    return (36*r)+(6*g)+b+16;
}

inline constexpr uint8_t get_seq(rgb& x)
{
    return get_seq(x.r,x.g,x.b);
}

inline void testGetSEQ()
{
    cli().clear();

    constexpr uint8_t clr = get_seq(0,179,255);

    cli().setChar(0,0,cchar("#############################",clr));

    std::cout<<"\n";
}

inline constexpr void seq2rgb(uint8_t &x)
{
    if(x==0)x=0;
    else if(x==1)x=95;
    else if(x==2)x=135;
    else if(x==3)x=175;
    else if(x==4)x=215;
    else if(x==5)x=255;
}

inline constexpr void get_rgb(uint8_t sequence,uint8_t &r,uint8_t &g,uint8_t &b)
{
    sequence -= 16;
    if(sequence >= 36)
    {
        r = sequence / 36;
        sequence = sequence % 36;
    }
    if(sequence >= 6)
    {
        g = sequence / 6;
        sequence = sequence % 6;
    }
    b = sequence;
    seq2rgb(r);
    seq2rgb(g);
    seq2rgb(b);
}

inline constexpr void get_rgb(uint8_t sequence,rgb& x)
{
    return get_rgb(sequence,x.r,x.g,x.b);
}

inline void testGetRGB()
{
    uint8_t r=0;
    uint8_t g=0;
    uint8_t b=0;
    get_rgb(24,r,g,b);
    std::cout<<(int)r<<" "<<(int)g<<" "<<(int)b<<"\n";
}

int main(int argc,char** argv)
{
    //rgb a("FF10FF");
    //a.print();
    std::cerr << from16to10("0f0123") << '\n';
    //test();
    return 0;
}
