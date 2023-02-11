#include "../lib/cuit.hpp"

int main()
{
    printf(ccs::DECSET(ccs::X11MR2)); // send second level mouse report control sequence

    // get events from mouse in terminal
    // maybe store x,y (?)
    // extract ncurses *.c lib
}