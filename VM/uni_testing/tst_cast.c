#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	int a;
	int b = 0x0000ffff;
	short c;
	int d;

	a = (short)b;
	printf("Passing value with short cast\n");
	printf("a int : %d\nb int : %d\n\n", a, b);
	c = 0;
	c = 0xff;
	c <<= 8;
	c += 0xff;
	d = 0;
	d = 0xff;
	d <<= 8;
	d += 0xff;
	printf("Writing to memory directly\n");
	printf("c short : %d\nd int : %d\n\n", c, d);
	exit(0);
}
