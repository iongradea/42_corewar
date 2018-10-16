#include <stdio.h>
#include <unistd.h>

char	*g_color[8] = {0, "\033[34m", "\033[32m", "\033[33m",
	"\033[35m", "\033[36m", "\033[37m", "\033[31m"};
char	*g_colorpc[8] = {0, "\033[44m", "\033[42m", "\033[43m",
	"\033[41m", "\033[45m", "\033[46m", "\033[47m"};

#define xxx g_color[1]

int main(void)
{
	write(1, "\033[0mxxx", 7);
	write(1, "\033[1mxxx", 7);
	write(1, "\033[31mxxx", 8);
	write(1, "\x1b[31mxxx", 8);
	write(1, "\x1b[30mxxx", 8);
	write(1, "\033[30mgrey", 20);
	write(1, "\033[1m\033[30mxxx", 20);
	exit(0);
}
