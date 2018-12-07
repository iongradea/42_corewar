/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:21:45 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/29 17:53:18 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int		ft_valid_opcode(int opcode)
{
	int			i;

	i = -1;
	while (++i < NB_OP)
		if (opcode == op_tab[i].opcode)
			return (true);
	return (false);
}

static int		ft_cycle_len(int opcode)
{
	int			i;

	i = -1;
	while (++i < NB_OP)
	{
		if (opcode == op_tab[i].opcode)
		{
			return (op_tab[i].cycle);
		}
	}
	//ft_printf("OPCODE INVALID \n");
	return (2);
}

void			cpu_checks(t_vm_mem *vm, t_ps *ps)
{
	DEBUG ? ft_printf("launching cpu_checks ...\n") : DEBUG;
	//if (vm->check >= vm->cycle_to_die + 1)
	DEBUG ? ft_printf("R CYCLE%d\n CYCLE%d\n", vm->real_cycle, vm->cycle) : DEBUG;
	if (vm->cycle % vm->cycle_to_die == 0)
	{
	//ft_printf("ps->playr = %s\nJe suis en vie !\nps->live = %d\n -- cycles %d\n\n ", ps->playr, ps->live, vm->cycle);
		1 ? ft_printf("KILL_RESET - check : %d - cycle_to_die : %d\n", \
									vm->check, vm->cycle_to_die) : DEBUG;

		ft_nb_live(ps) > NBR_LIVE ? vm->cycle_to_die -= CYCLE_DELTA : true;
		vm->lives = 0;

		ft_kill_reset_ps(ps);
		vm->check++;
		vm->real_cycle = 0;
	}
	if (vm->check == MAX_CHECKS)
	{
		1 ? ft_printf("MAX_CHECKS - vm->check : %d - MAX_CHECKS : %d\n", \
									vm->check, MAX_CHECKS) : DEBUG;
		vm->cycle_to_die -= CYCLE_DELTA;
		g_verbose == 3 ? ft_printf("Cycle to die is now at %d\n", \
											vm->cycle_to_die) : g_verbose;
		vm->check = 0;
	}

}

int				exec_op(t_vm_mem *vm, t_ps *lst_ps)
{
	int i;
	int j;
	t_ps *tmp;

	i = 0;
	j = -1;
	//tmp = lst_ps;
	//while (tmp && (++i || true))
		//tmp = tmp->next;
	while (lst_ps)// && (++j < i))// && lst_ps->cyc_len >= 0)
	{
		tmp = lst_ps;
		//ft_printf("ps_uid : %d - fl : %d\n", lst_ps->ps_uid, lst_ps->fl);
		if (lst_ps->fl == true)
		{
			lst_ps->opcode = *(vm->mem + MEM_CIR_POS(lst_ps->pc));
			//ft_printf("lst_ps->ps_uid : %d - opcode : %#04x\n", lst_ps->ps_uid, lst_ps->opcode);
			lst_ps->cyc_len = ft_cycle_len(lst_ps->opcode) - 1;
			lst_ps->fl = false;
		}
		if (lst_ps->cyc_len == 0)
		{
			lst_ps->fl = true;
			if (!ft_valid_opcode(lst_ps->opcode))
			{
				lst_ps->op_size = 1;
				ft_next_op(lst_ps, NO_CARRY);
			}
			else
			{
				if (!ft_strcmp("live", op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo))
					vm->lives++;
				g_verbose == 4 ? ft_printf("cycle : %d | player %d | ps_uid : %d | ps->pc : %d | %s\n", \
					vm->cycle, lst_ps->uid, lst_ps->ps_uid, lst_ps->pc, op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo) : g_verbose;
				op_tab[OP_TAB_INDEX(tmp->opcode)].fun(vm, tmp, \
														tmp->opcode);
			}
		}
		//ft_printf("vm->cycle : %d\n", vm->cycle);
		lst_ps->cyc_len--;
		lst_ps = lst_ps->next;
	}
	return (EXIT_SUCCESS);
}
