#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/inc/libft.h"

int main(int ac, char **av)
{
	int fd;
	int fd1;

	fd = open(av[1], O_RDONLY);
	printf("%#010x\n",fd + 0x00000020); 
	printf("%c\n",fd + 0x00000020); 
	fd1 = fd + 0x20;
	print_memory(&fd1, 1);
	printf("%d\n", sizeof(char*));
	write(1, &fd1, 4);
	exit(0);
}
