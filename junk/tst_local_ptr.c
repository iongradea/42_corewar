# include <unistd.h>
# include <stdio.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"

char *fun(void)
{
	char *str;

	str = malloc(13);
	//bzero(str, 20);
	memcpy(str, "hello world\n\0", 13);
	write(1, "fun\n", 4);
	return (str);
}

int main(void)
{
	char *str;

	write(1, "before\n", 7);
	//write(1, &str, 30);
	//str = fun();
	memcpy(str, fun(), 13);
	write(1, "here\n", 5);
	write(1, str, 13);
	ft_printf("\n%p : %s\n", str, str);
	printf("%s\n", str);
	exit(0);
}
