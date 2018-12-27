/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ncurse_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:56:06 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/16 15:24:47 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static t_ps		*ft_curr_ps_pc(t_ps *ps, int i)
{
	t_ps	*tmp;

	tmp = ps;
	while (tmp)
	{
		if (tmp->pc == i && tmp->live != PS_DEAD)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void			ft_print_arena(t_vm_mem *vm, t_ps *ps)
{
	int			i;
	t_ps		*tmp;

	i = 0;
	erase();
	ft_init_arena(vm, ps);
	while (i < MEM_SIZE)
	{
		tmp = ps;
		if (ft_is_pc(ps, i))
		{
			tmp = ft_curr_ps_pc(ps, i);
			attron(COLOR_PAIR(tmp->color_pc));
			printw("%02x", 0xFF & vm->mem[i]);
			attroff(COLOR_PAIR(tmp->color_pc));
		}
		else
			ft_print_arena_2(vm, i);
		printw(" ");
		if ((i + 1) % MEM_LINE_LENGTH == 0)
			printw("\n");
		i++;
	}
	ft_print_game_stats(vm, ps);
}

void			ft_print_arena_2(t_vm_mem *vm, int i)
{
	vm->a[i].color != UNDEFINED ? attron(COLOR_PAIR(vm->a[i].color)) \
								: true;
	printw("%02x", 0xFF & vm->mem[i]);
	vm->a[i].color != UNDEFINED ? attroff(COLOR_PAIR(vm->a[i].color)) \
								: true;
}

void			ft_ncurse(t_vm_mem *vm, t_ps *ps)
{
	t_ps		*tmp;

	tmp = ps;
	ft_init_ncurses();
	ft_print_arena(vm, tmp);
}
