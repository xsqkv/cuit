#include "../lib/cuit.hpp"

int main()
{
    cli::clear();

    square sqr({5,5,1},25,'#',1);

    sqr.draw();
}