/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ncurse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:53:12 by romontei          #+#    #+#             */
/*   Updated: 2018/11/06 21:58:16 by romontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"


void	ft_init_arena(t_vm_mem *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		vm->a[i].hex = 0;
		vm->a[i].color = 12;
		vm->a[i].prevcolor = 12;
		vm->a[i].occupied = 0;
		vm->a[i].new_color_count = 0;
		i++;
	}
}

//void	ft_print_game_stats(t_vm_mem *vm)
//{
//	int i;
//
//	i = -1;
//	while (++i < vm->player_amount)
//		ft_print_lives(e, i);
//	attron(COLOR_PAIR(14));
//	printw("\n\nCycle: %-10d Cursors: %-10d Total Number of lives: %d/%-10d \
//			Checks: %d/9 > Decrease cycle to die with: %d     \
//			Cycles to die: %d/%d\n\n", e->tot_cycle, e->cursors, NBR_LIVE, e->lives, \
//			e->check, CYCLE_DELTA, e->cycles_to_die, e->cycle);
//	attroff(COLOR_PAIR(14));
//	refresh();
//}

void	ft_init_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_GREEN);
	init_pair(14, COLOR_GREEN, COLOR_BLACK);
	curs_set(FALSE);
}

void	ft_print_arena(t_vm_mem *vm)
{
	int i;

	i = 0;
	erase();
	while (i < MEM_SIZE)
	{
		if (vm->a[i].new_color_count > 0)
			attron(A_BOLD);
		attron(COLOR_PAIR(vm->a[i].color));
		printw("%02x", 0xFF & vm->a[i].hex);
		attroff(COLOR_PAIR(vm->a[i].color));
		if (vm->a[i].new_color_count > 0)
		{
			attroff(A_BOLD);
			vm->a[i].new_color_count -= 1;
		}
		printw(" ");
		if ((i + 1) % (128 / 2) == 0)
			printw("\n");
		i++;
	}
	//	ft_print_game_stats(vm);
}

void		ft_ncurse(t_vm_mem *vm)
{
	ft_print_arena(vm);
	ft_printf("00");
	refresh();
}

