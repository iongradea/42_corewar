#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *str;

	perror("xxperror");
	str = strerror(2);
	printf("xxx : %s\n", str);
	write(1, "write\n", 6);
	printf("sizeof int : %d\n", sizeof(int));
	exit(0);
}
