#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int		reg[2];
	int i;

	i = -1;
	reg[0] = 0;
	reg[1] = 0;
	while (++i < 4 - 1 && ((reg[1] <<= 8) || 1))
	{
		printf("i : %d\n", i);
		reg[1] += 0xff;
	}
	printf("reg[0] = %#010x\n", reg[0]);
	printf("reg[1] = %#010x\n", reg[1]);
	exit(0);
}
