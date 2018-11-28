/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:21:45 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/16 17:42:06 by romontei         ###   ########.fr       */
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
			return (op_tab[i].cycle);
	}
	return (1);
}

void			cpu_checks(t_vm_mem *vm, t_ps *ps)
{
	DEBUG ? ft_printf("launching cpu_checks ...\n") : DEBUG;
	//if (vm->check >= vm->cycle_to_die + 1)
	DEBUG ? ft_printf("R CYCLE%d\n CYCLE%d\n", vm->real_cycle, vm->cycle) : DEBUG;
	if (vm->cycle % vm->cycle_to_die == 0)
	{
	ft_printf("ps->playr = %s\nJe suis en vie !\nps->live = %d\n -- cycles %d\n\n ", ps->playr, ps->live, vm->cycle);
		DEBUG ? ft_printf("KILL_RESET - check : %d - cycle_to_die : %d\n", \
									vm->check, vm->cycle_to_die) : DEBUG;
		ft_kill_reset_ps(ps);
		vm->check++;
		vm->real_cycle = 0;
	}
	if (ft_nb_live(ps) > NBR_LIVE)
	{
		ft_reset_ps(ps);
		DEBUG ? ft_printf("NB_LIVE - ft_nb_live(ps) : %d - NBR_LIVE : %d\n", \
									ft_nb_live(ps), NBR_LIVE) : DEBUG;
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->lives = 0;
		vm->check = 0;
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

int				exec_op(t_vm_mem *vm, t_ps *lst_ps)
{
	while (lst_ps)// && lst_ps->cyc_len >= 0)
	{
		if (lst_ps->cyc_len == 0)
		{
			lst_ps->opcode = *(vm->mem + MEM_CIR_POS(lst_ps->pc));
			lst_ps->cyc_len = ft_cycle_len(lst_ps->opcode);
			if (!ft_valid_opcode(lst_ps->opcode))
			{
				lst_ps->op_size = 1;
				return (ft_next_op(lst_ps, NO_CARRY));
			}
			else
			{
				if (!ft_strcmp("live", op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo))
					vm->lives++;
				g_verbose == 4 ? ft_printf("%s\n", \
					op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo) : g_verbose;
				op_tab[OP_TAB_INDEX(lst_ps->opcode)].fun(vm, lst_ps, \
														lst_ps->opcode);
			}
		}
		lst_ps->cyc_len--;
		lst_ps = lst_ps->next;
	}
	return (EXIT_SUCCESS);
}
