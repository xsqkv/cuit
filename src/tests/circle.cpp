#include "../lib/cuit.hpp"

int main()
{
    cli::clear();

    printf(EXSTR(RED_FG)); // don't works

    circle sqr({15,15,1},{5,5,1},'#'); // need to do cache string for shapes

    printf(EXSTR(RIS)); // don't works

    sqr.draw();
}