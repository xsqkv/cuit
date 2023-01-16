#include "../lib/cuit.hpp"

using namespace cli;

int main()
{
	cli::setColor(12,0,0);
	printf("AB");
	cli::resetColor();

	cli::setColor(0,12,0);
	printf("00");
	cli::resetColor();

	cli::setColor(0,0,127);
	printf("BA\n");
	cli::resetColor();
}
