/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/11/09 18:44:56 by romontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int		ft_get_dist(t_ps *ps)
{
	int			code_size;
	int			nb_ps;

	code_size = 0;
	nb_ps = 0;
	while (ps)
	{
		code_size += ps->code_size;
		nb_ps++;
		ps = ps->next;
	}
	return ((MEM_SIZE - code_size) / nb_ps);
}

/*
** code starts at beginning of line (visual display)
*/

static void		ft_cpy_code(t_vm_mem *vm, t_ps *ps, int *j)
{
	int			i;

	i = -1;
	while (*j % MEM_LINE_LENGTH)
		(*j)--;
	ps->pc = MEM_CIR_POS(*j);
	while (++i < ps->code_size)
	{
		vm->mem_uid[(*j)] = ps->uid;
		DEBUG > 1 ? ft_printf("vm->\n") : DEBUG;
		vm->mem[(*j)++] = ps->code[i];
	}
}

void			ft_set_colors(t_vm_mem *vm)
{
	int			i;

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

t_vm_mem		*ft_new_mem(void)
{
	t_vm_mem	*vm;

	if (!(vm = (t_vm_mem*)ft_memalloc(sizeof(t_vm_mem))))
		exit(ERROR_MSG("ft_new_mem : error heap allocation"));
	ft_bzero(vm->mem, MEM_SIZE);
	vm->cycle = 0;
	vm->real_cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->ch_decr = 0;
	vm->check = 0;
	vm->opt = 0x00;
	vm->display = 0;
	vm->dump = 0;
	vm->lives = 0;
	ft_memset(vm->mem_uid, NO_PLAYR, sizeof(vm->mem_uid));
	ft_bzero(vm->mem_color, sizeof(vm->mem_color));
	vm->mem_color_size = 0;
	vm->mem_color_ind = 0;
	vm->last_live = NO_PLAYR;
	//ft_set_colors(vm);
	return (vm);
}

void			add_data_vm(t_vm_mem *vm, t_ps *ps)
{
	int			j;
	int			dist;

	j = 0;
	vm->nb_players = 1;
	dist = ft_get_dist(ps);
	ft_cpy_code(vm, ps, &j);
	j += dist;
	ps = ps->next;
	while (ps)
	{
		ft_cpy_code(vm, ps, &j);
		j += dist;
		ps = ps->next;
		vm->nb_players++;
	}
}
