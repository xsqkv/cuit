// terminal sequence color class file

#pragma once

#include<iostream>

#include "rgb.hpp"

class seqColor
{
   public:

   // rgb to sequence digit
   static inline constexpr void rgb2seq(uint8_t &x)
   {
      if(x < 47)x=0;
      else if(x >= 47 && x < 115)x=1;
      else if(x >= 115 && x < 155)x=2;
      else if(x >= 155 && x < 195)x=3;
      else if(x >= 195 && x < 235)x=4;
      else x=5;
   }

   // sequence digit to rgb
   static inline constexpr void seq2rgb(uint8_t &x)
   {
      if(x==0)x=0;
      else if(x==1)x=95;
      else if(x==2)x=135;
      else if(x==3)x=175;
      else if(x==4)x=215;
      else if(x==5)x=255;
   }

   uint8_t color;
   
   // print sequence color value
   inline constexpr void print()
   {
      printf("%d\n",color);
   }

   // from RGB to sequence color
   inline constexpr void fromRGB(uint8_t r,uint8_t g,uint8_t b)
   {
      rgb2seq(r);
      rgb2seq(g);
      rgb2seq(b);
      color = (36*r)+(6*g)+b+16;
   }

   // from sequence color to RGB
   inline constexpr void toRGB(uint8_t &r,uint8_t &g,uint8_t &b)
   {
      color -= 16;
      if(color >= 36)
      {
         r = color / 36;
         color = color % 36;
      }
      if(color >= 6)
      {
         g = color / 6;
         color = color % 6;
      }
      b = color;
      seq2rgb(r);
      seq2rgb(g);
      seq2rgb(b);
   }

   // default constructor
   inline constexpr seqColor() : color(0) {}

   // setter constructor
   inline constexpr seqColor(uint8_t Color)
   {
      color = Color;
   }

   // setter constructor
   inline constexpr seqColor(uint8_t r,uint8_t g,uint8_t b)
   {
      fromRGB(r,g,b);
   }

};