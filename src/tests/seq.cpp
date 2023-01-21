#include "../lib/cuit.hpp"

int main()
{
	cli::beginColor(12,0,0);
	printf("AB");
	cli::endColor();

	cli::beginColor(0,12,0);
	printf("00");
	cli::endColor();

	cli::beginColor(0,0,127);
	printf("BA\n");
	cli::endColor();
}
