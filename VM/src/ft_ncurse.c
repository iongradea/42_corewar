/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ncurse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:53:12 by romontei          #+#    #+#             */
/*   Updated: 2018/11/18 14:30:03 by romontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void	ft_parsing(t_vm_mem *vm, t_ps *ps)
{
	int		i;
	int		k;

	i = -1;
	while (++i < vm->nb_players)
	{
		k = PROG_NAME_LENGTH + COMMENT_LENGTH + 16;
		ps->inst_len = k;
	}
}

void	ft_player_to_arena(t_vm_mem *vm, t_ps *ps, int i, int *k)
{
	int		count;

	count = 0;
	while (ps && count < ps->inst_len)
	{
		vm->a[*k].hex = 0xFF & ps->inst[count];
		vm->a[*k].color = 1 + (i % 6);
		vm->a[*k].prevcolor = 1 + (i % 6);
		*k += 1;
		count++;
		ps = ps->next;
	}
}

void	ft_build_arena(t_vm_mem *vm, t_ps *ps)
{
	int			i;
	static int	k;

	i = -1;
	k = 0;
	while (++i < vm->nb_players)
	{
		ps->index_start = (MEM_SIZE / vm->nb_players) * i;
		k = (MEM_SIZE / vm->nb_players) * i;
		ft_player_to_arena(vm, ps, i, &k);
	}
}


void	ft_print_lives(t_vm_mem *vm, int i)
{
	int k;
	int cycles;
	//attron(COLOR_PAIR(vm->a[MEM_SIZE / vm->nb_players * i].color));
	attron(COLOR_PAIR(vm->ps[i].color));
	cycles = (vm->ps[i].live < 161) ? vm->ps[i].live : 161;
	k = -1;
	printw("\nLives for %-15s", vm->ps[i].playr);
	printw("%-5d", vm->ps[i].live);
	while (++k < cycles)
		addch(ACS_CKBOARD);
	//attroff(COLOR_PAIR(vm->a[MEM_SIZE / vm->nb_players * i].color));
	attroff(COLOR_PAIR(vm->ps[i].color));
}

void	ft_print_game_stats(t_vm_mem *vm)
{
	int i;
	i = -1;
	while (++i < vm->nb_players)
		ft_print_lives(vm,  i);
	attron(COLOR_PAIR(14));
	printw("\n\nCycle: %-10d Total Number of lives: %d/%-10d \
			Checks: %d/9 > Decrease cycle to die with: %d     \
			Cycles to die: %d/%d\n\n", vm->cycle, vm->lives, NBR_LIVE, \
			vm->check, CYCLE_DELTA, vm->cycle_to_die, vm->real_cycle);
	attroff(COLOR_PAIR(14));
	refresh();
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
	ft_print_game_stats(vm);
}

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

void		ft_ncurse(t_vm_mem *vm, t_ps *ps)
{
	t_ps *tps;

	tps = ps;
	ft_print_arena(vm);
	//usleep(300);
}

