/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/12/08 16:58:29 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int		ft_get_dist(t_ps *ps)
{
	int			code_size;
	int			nb_ps;

	DEBUG ? ft_printf("launching ft_get_dist ...\n") : DEBUG;
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
	DEBUG ? ft_printf("launching ft_cpy_code ...\n") : DEBUG;
	ps->pc = ft_mem_cir_pos(*j);
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
	DEBUG ? ft_printf("launching ft_set_colors ...\n") : DEBUG;
	while (i < MEM_SIZE)
	{
		vm->a[i].hex = 0;
		vm->a[i].playr_uid = UNDEFINED;
		vm->a[i].color = 0;
		vm->a[i].color_pc = 0;
		i++;
	}
}

t_vm_mem		*ft_new_mem(void)
{
	t_vm_mem	*vm;

	DEBUG ? ft_printf("launching ft_new_mem ...\n") : DEBUG;
	if (!(vm = (t_vm_mem*)ft_memalloc(sizeof(t_vm_mem))))
		exit(ERROR_MSG("ft_new_mem : error heap allocation"));
	ft_bzero(vm->mem, MEM_SIZE);
	vm->cycle = 1;
	vm->real_cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->ch_decr = 0;
	vm->check = 0;
	vm->opt = 0x00;
	vm->dump = 0;
	vm->display = 0;
	ft_memset(vm->mem_uid, NO_PLAYR, sizeof(vm->mem_uid));
	ft_bzero(vm->mem_color, sizeof(vm->mem_color));
	vm->mem_color_size = 0;
	vm->mem_color_ind = 0;
	ft_bzero(vm->playr_uid, sizeof(vm->playr_uid));
	vm->nb_players = 0;
	vm->lives = 0;
	vm->last_live = NO_PLAYR;
	ft_bzero(vm->playr_live, sizeof(vm->playr_live));
	vm->ps_st = NULL;
	return (vm);
}

void			add_data_vm(t_vm_mem *vm, t_ps *ps)
{
	int			j;
	int			dist;
	t_ps		*lst;

	DEBUG ? ft_printf("launching add_data_vm ...\n") : DEBUG;
	lst = ps;
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
	j = -1;
	while (lst)
	{
		vm->playr_uid[++j] = lst->uid;
		lst = lst->next;
	}
}
