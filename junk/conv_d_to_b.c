#include "../libft/inc/libft.h"
#include "../libft/inc/get_next_line.h"
#include "../libft/inc/ft_printf.h"

int main(int ac, char **av)
{
	ft_printf("%08b\n", ft_atoi(av[1]));
	ft_printf("%x\n", ft_atoi(av[1]));
	exit (0);
}
