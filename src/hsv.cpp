#include "hsv.h"

inline constexpr void hsv::print()
{
    printf("%3.1f %3.1f%% %3.1f%% \n",h,s,v);
}