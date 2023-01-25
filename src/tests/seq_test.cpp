#include "../lib/cuit.hpp"

int main()
{
    printf(ccs::RIS); // Clear
    printf("%s01;38;05;128mABOBA%sm\n", ccs::CSI, ccs::CSI);
}