#include "VM/inc/vm.h"

int main(void)
{
	int i;
	char **tab;

	i = 0;
	tab = ft_strsplit_c("	sti		r1, %:alive, %1  ", ',');
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);

		i++;
	}
	ft_printf("%d\n", ft_arrlen(tab));
	exit(0);
}
