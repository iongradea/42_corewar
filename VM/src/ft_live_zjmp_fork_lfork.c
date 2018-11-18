/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live_zjmp_fork_lfork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:31:38 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/18 14:42:10 by romontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
** DEBUG ? ft_printf("launching ft_live ...\n") : DEBUG;
** DEBUG ? ft_printf("un processus dit que le joueur %d(%s) est en vie\n", \
**													ps->uid, ps->playr) : DEBUG;
*/

int					ft_live(t_vm_mem *vm, t_ps *ps, int opcode)
{
	unsigned int	arg0;
	t_ps			*lst;
	int				i;

	(void)opcode;
	i = -1;
	arg0 = 0;
	while (++i < DIR_SIZE(OP_TAB_INDEX(LIVE)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + MEM_CIR_POS(ps->pc + OPCODE_SIZE + i));
	lst = ps;
	while (lst)
	{
		if (lst->uid == (int)arg0)
			break ;
		lst = lst->next;
	}
	DEBUG ? print_memory(vm->mem + ps->pc, OPCODE_SIZE \
								+ DIR_SIZE(OP_TAB_INDEX(LIVE))) : DEBUG;
	if (lst == NULL)
		lst = ps;
	lst->live++;
	//ft_printf("ps->playr = %s\nJe suis en vie !\nps->live = %d\n\n", ps->playr, ps->live);
	vm->last_live = lst->uid;
	ps->op_size = OPCODE_SIZE + DIR_SIZE(OP_TAB_INDEX(LIVE));
	return (ft_next_op(ps, NO_CARRY));
}

int					ft_zjmp(t_vm_mem *vm, t_ps *ps, int opcode)
{
	unsigned int	arg0;
	int				i;

	(void)opcode;
	i = -1;
	arg0 = 0;
	DEBUG ? ft_printf("launching ft_zjmp ...\n") : DEBUG;
	while (++i < DIR_SIZE(OP_TAB_INDEX(ZJMP)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + MEM_CIR_POS(ps->pc + OPCODE_SIZE + i));
	if (ps->carry == CARRY_TRUE)
		ps->pc = MEM_CIR_POS(ps->pc + (arg0 % IDX_MOD));
	return (EXIT_SUCCESS);
}

int					ft_fork(t_vm_mem *vm, t_ps *ps, int opcode)
{
	t_ps			*new;
	unsigned int	arg0;
	int				i;

	i = -1;
	arg0 = 0;
	DEBUG ? ft_printf("launching ft_fork ...\n") : DEBUG;
	while (++i < DIR_SIZE(OP_TAB_INDEX(FORK)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + MEM_CIR_POS(ps->pc + OPCODE_SIZE + i));
	new = ft_cpy_playr(ps, vm);
	if (opcode == FORK)
		new->pc = MEM_CIR_POS(ps->pc + (arg0 % IDX_MOD));
	else if (opcode == LFORK)
		new->pc = MEM_CIR_POS(ps->pc + arg0);
	ps->op_size = OPCODE_SIZE + DIR_SIZE(OP_TAB_INDEX(FORK));
	return (ft_next_op(ps, NO_CARRY));
}
