#include "../inc/ft_printf.h"

int main(void)
{
	ft_printf("%sred%s%sgreen%s!\n", RED, EOC, GREEN, EOC);
	ft_printf("%sbold%s%sblack%s!\n", BOLD, EOC, UNDERLINE, EOC);
	ft_printf("%scyan%s%spurple%s!\n", CYAN, EOC, PURPLE, EOC);
	ft_printf("%sblue%s%syellow%s!\n", BLUE, EOC, YELLOW, EOC);

	ft_printf("%sred%s%sgreen%s!\n", RED_B, EOC, GREEN_B, EOC);
	ft_printf("%sbold%s%sblack%s!\n", RED_B, EOC, GREY, EOC);
	ft_printf("%scyan%s%spurple%s!\n", CYAN_B, EOC, PURPLE_B, EOC);
	ft_printf("%sblue%s%syellow%s!\n", BLUE_B, EOC, YELLOW_B, EOC);
	exit(0);
}
