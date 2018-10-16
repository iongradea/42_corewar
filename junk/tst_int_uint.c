#include <stdio.h>

int main(void)
{
	unsigned int i;
	int j = -1;

	i = (unsigned int)j;
	printf("%x\n", i);
	exit(0);
}
