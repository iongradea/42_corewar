/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ncurse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:53:12 by romontei          #+#    #+#             */
/*   Updated: 2018/12/08 16:00:12 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
** init_pair(0, COLOR_YELLOW, COLOR_BLACK);
** init_pair(1, COLOR_BLUE, COLOR_BLACK);
** init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
** init_pair(3, COLOR_CYAN, COLOR_BLACK);
** init_pair(4, COLOR_RED, COLOR_BLACK);
** init_pair(5, COLOR_GREEN, COLOR_BLACK);
** init_pair(6, COLOR_YELLOW, COLOR_BLACK);
** init_pair(7, COLOR_BLACK, COLOR_BLUE);
** init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
** init_pair(9, COLOR_BLACK, COLOR_CYAN);
** init_pair(10, COLOR_BLACK, COLOR_RED);
** init_pair(11, COLOR_BLACK, COLOR_GREEN);
** init_pair(12, COLOR_WHITE, COLOR_BLACK);
** init_pair(13, COLOR_BLACK, COLOR_GREEN);
*/

void			ft_init_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(7, COLOR_WHITE, COLOR_CYAN);
	init_pair(8, COLOR_WHITE, COLOR_RED);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	curs_set(FALSE);
}

void			ft_print_lives(t_vm_mem *vm, t_ps *ps, int i)
{
	int			k;
	int			cycles;

	attron(COLOR_PAIR(vm->a[MEM_SIZE / vm->nb_players * i].color));
	cycles = (ps->live < 161) ? ps->live : 161;
	k = -1;
	printw("\nplayr %s (%d)", ps->playr, ps->uid);
	printw("\nLives : %-5d", ps->live);
	while (++k < cycles)
		addch(ACS_CKBOARD);
	attroff(COLOR_PAIR(vm->a[MEM_SIZE / vm->nb_players * i].color));
}

void			ft_print_game_stats(t_vm_mem *vm, t_ps *ps)
{
	int			i;
	t_ps		*lst;

	i = -1;
	lst = ps;
	while (++i < vm->nb_players && ps)
	{
		ft_print_lives(vm, ps, i);
		ps = ps->next;
	}
	i = -1;
	while (lst && (++i || true))
		lst = lst->next;
	attron(COLOR_PAIR(9));
	printw("\n\nNb of processes : %d\n\n", i);
	printw("\n\nCycle: %-10d Total Number of lives: %d/%-10d \
			Checks: %d/%d > Decrease cycle to die with: %d \
			Cycles to die: %d/%d\n\n", vm->cycle, vm->lives, NBR_LIVE, \
			vm->check, MAX_CHECKS, CYCLE_DELTA, vm->cycle_to_die, \
			vm->real_cycle);
	attroff(COLOR_PAIR(9));
	refresh();
}

static int		ft_get_playr_index(t_vm_mem *vm, int uid)
{
	int			i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (vm->playr_uid[i] == uid)
			return (i);
	}
	return (uid);
}

void			ft_init_arena(t_vm_mem *vm)
{
	int 		i;
	int 		index;

	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->a[i].hex = vm->mem[i];
		vm->a[i].playr_uid = vm->mem_uid[i];
		index = ft_get_playr_index(vm, vm->mem_uid[i]);
		vm->a[i].color = index != UNDEFINED ? 1 + (index % 4) : UNDEFINED;
		vm->a[i].color_pc = index != UNDEFINED ? \
						1 + (index % 4) + 4 : UNDEFINED;
	}
}
