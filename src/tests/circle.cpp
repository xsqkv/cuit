#include "../lib/cuit.hpp"

int main()
{
    cli::clear();

    //setbuf(stdout,NULL); //SLOW

    circle sqr({30,31,1},{5,5,1},'#'); // need to do cache string for shapes

    sqr.draw();

}