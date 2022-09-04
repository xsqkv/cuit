#include <iostream>
#include "lib/cuit.h"


// ======== CUI =========
// Global Variables
bool EXTENDED_COLORS = 1;
bool PSEUDO_GRAPHICS = 1;
bool CUSTOM_FONT = 0;
bool USE_SCALING = 0;


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
    auto a = min(9.6,3.6,4.6);

    printf("%F \n",a);

    return 0;
}
