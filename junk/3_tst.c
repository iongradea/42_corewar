#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av)
{
	int fd;
	int rd;
	char buf[10];

	fd = open(av[1], O_RDONLY);
	lseek(fd, 0, SEEK_SET);
	while ((rd = read(fd, buf, 10) != 0))
		printf("%s\n", buf);
	exit(0);
}
