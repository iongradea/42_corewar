/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2018/10/24 18:17:49 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/vm.h"

static int  ft_valid_opcode(int opcode)
{
	int i;

	i = -1;
	while (++i < NB_OP)
		if (opcode == op_tab[i].opcode)
			return (true);
	return (false);
}

static int  ft_cycle_len(int opcode)
{
	int i;

	i = -1;
	while (++i < NB_OP)
	{
		if (opcode == op_tab[i].opcode)
			return (op_tab[i].cycle);
	}
	return (1);
}

int   exec_op(t_vm_mem *vm, t_ps *ps)
{
	int   opcode;
	int   cyc_len;

	DEBUG ? ft_printf("launching exec_op ...\n") : DEBUG;
	opcode = *(vm->mem + MEM_CIR_POS(ps->pc));
	cyc_len = ft_cycle_len(opcode);
	DEBUG ? (ft_valid_opcode(opcode) ? ft_printf("opcode : %d - op : %s\n", opcode, op_tab[OP_TAB_INDEX(opcode)].mmemo) : ft_printf("opcode : %d\n", opcode)) : DEBUG;
	while (cyc_len >= 0)
	{
		if (cyc_len == 0)
		{
			if (!ft_valid_opcode(opcode))
			{
				ps->op_size = 1;
				return (ft_next_op(ps, NO_CARRY));
			}
			else
				op_tab[OP_TAB_INDEX(opcode)].fun(vm, ps, opcode);
		}
		cyc_len--;
	}
	return (EXIT_SUCCES);
}
