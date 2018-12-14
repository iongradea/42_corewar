/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:21:45 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/14 15:41:08 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int		ft_valid_opcode(int opcode)
{
	int			i;

	i = -1;
	while (++i < NB_OP)
		if (opcode == g_op_tab[i].opcode)
			return (true);
	return (false);
}

static int		ft_cycle_len(int opcode)
{
	int			i;

	i = -1;
	while (++i < NB_OP)
	{
		if (opcode == g_op_tab[i].opcode)
		{
			return (g_op_tab[i].cycle);
		}
	}
	return (2);
}

/*
** DEBUG ? ft_printf("launching cpu_checks ...\n") : DEBUG;
** DEBUG ? ft_printf("R CYCLE%d\n CYCLE%d\n", vm->real_cycle, vm->cycle) \
** : DEBUG;
*/

void			cpu_checks(t_vm_mem *vm, t_ps *ps)
{
	if (vm->cycle % vm->cycle_to_die == 0)
	{
		DEBUG ? ft_printf("KILL_RESET - check : %d - cycle_to_die : %d\n", \
									vm->check, vm->cycle_to_die) : DEBUG;
		ft_nb_live(ps) > NBR_LIVE ? vm->cycle_to_die -= CYCLE_DELTA : true;
		vm->lives = 0;
		ft_kill_reset_ps(vm);
		vm->check++;
		vm->real_cycle = 0;
	}
	if (vm->check == MAX_CHECKS)
	{
		DEBUG ? ft_printf("MAX_CHECKS - vm->check : %d - MAX_CHECKS : %d\n", \
									vm->check, MAX_CHECKS) : DEBUG;
		vm->cycle_to_die -= CYCLE_DELTA;
		g_verbose == 3 ? ft_printf("Cycle to die is now at %d\n", \
											vm->cycle_to_die) : g_verbose;
		vm->check = 0;
	}
}

/*
**	If opcode after cycles not match with current opcode
**	need to jump to next op
*/

int				exec_op_2(t_ps *lst_ps, t_vm_mem *vm, t_ps *tmp)
{
	int			cur_opcode;

	lst_ps->fl = true;
	cur_opcode = *(vm->mem + ft_mem_cir_pos(lst_ps->pc));
	if (!ft_valid_opcode(lst_ps->opcode))
	{
		lst_ps->op_size = 2;
		return ft_next_op(lst_ps, NO_CARRY);
	}
	if (lst_ps->opcode != cur_opcode)
	{
		if (!check_ocp_fmt(vm, lst_ps, g_op_tab[lst_ps->opcode].nb_param))
			lst_ps->op_size = 2;
		else
			lst_ps->op_size = ft_op_size_2(vm, lst_ps);
		return ft_next_op(lst_ps, NO_CARRY);
	}
	if (!ft_strcmp("live", g_op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo))
		vm->lives++;
	g_verbose == 4 ? ft_printf("cycle : %d | player %d | ps_uid : %d | \
		ps->pc : %d | %s\n", vm->cycle, lst_ps->uid, lst_ps->ps_uid, \
		lst_ps->pc, g_op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo) : \
		g_verbose;
	g_op_tab[OP_TAB_INDEX(tmp->opcode)].fun(vm, tmp, tmp->opcode);
	return (EXIT_SUCCESS);
}

int				exec_op(t_vm_mem *vm, t_ps *lst_ps)
{
	int			i;
	int			j;
	t_ps		*tmp;

	i = 0;
	j = -1;
	while (lst_ps->next)
		lst_ps = lst_ps->next;
	while (lst_ps)
	{
		tmp = lst_ps;
		if (lst_ps->fl == true)
		{
			lst_ps->opcode = *(vm->mem + ft_mem_cir_pos(lst_ps->pc));
			lst_ps->cyc_len = ft_cycle_len(lst_ps->opcode) - 1;
			lst_ps->fl = false;
		}
		if (lst_ps->cyc_len == 0)
			exec_op_2(lst_ps, vm, tmp);
		lst_ps->cyc_len--;
		lst_ps = lst_ps->prev;
	}
	return (EXIT_SUCCESS);
}
