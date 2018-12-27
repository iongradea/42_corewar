#include <stdio.h>

int main(void)
{
	int i;

	i = -1;
	if (1 && i)
		printf("1st => i : %d\n", i);
	i = -1;
	if (1 && (i = 1))
		printf("2nd => i : %d\n", i);
	i = -1;
	if (1 && (i = 2 || 1))
		printf("3rd => i : %d\n", i);
	i = -1;
	if (1 && ((i = 0) || 1))
		printf("4th => i : %d\n", i);
	i = -1;
	if (1 && (i = 2 || 0))
		printf("5th => i : %d\n", i);
	i = -1;
	if (1 && 0 && (i = 2 || 0))
		1;
	printf("6th => i : %d\n", i);
	exit(0);
}
