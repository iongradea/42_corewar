/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2018/10/27 12:30:20 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int   ft_live(t_vm_mem *vm, t_ps *ps, int opcode)
{
	unsigned int  arg0;
	t_ps          *lst;
	int           i;

	(void)opcode;
	DEBUG ? ft_printf("launching ft_live ...\n") : DEBUG;
	i = -1;
	arg0 = 0;
	while (++i < DIR_SIZE(OP_TAB_INDEX(LIVE)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + MEM_CIR_POS(ps->pc + OPCODE_SIZE + i));
	lst = ps;
	while (lst)
	{
		if (lst->uid == (int)arg0)
			break;
		lst = lst->next;
	}
	//ft_printf("ft_live => lst : %p - arg0 : %d - ps->playr : %s\n", lst, arg0, ps->playr);
	DEBUG ? print_memory(vm->mem + ps->pc, OPCODE_SIZE + DIR_SIZE(OP_TAB_INDEX(LIVE))) : DEBUG;
	if (lst == NULL)
		lst = ps;
	lst->live++;
	vm->last_live = lst->uid;
	ps->op_size = OPCODE_SIZE + DIR_SIZE(OP_TAB_INDEX(LIVE));
	ft_printf("un processus dit que le joueur %d(%s) est en vie\n", ps->uid, ps->playr);
	return (ft_next_op(ps, NO_CARRY));
}

int   ft_zjmp(t_vm_mem *vm, t_ps *ps, int opcode)
{
	unsigned int  arg0;
	int           i;

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

int   ft_fork(t_vm_mem *vm, t_ps *ps, int opcode)
{
	t_ps  *new;
	unsigned int arg0;
	int   i;

	i = -1;
	arg0 = 0;
	DEBUG ? ft_printf("launching ft_fork ...\n") : DEBUG;
	while (++i < DIR_SIZE(OP_TAB_INDEX(FORK)) && ((arg0 = arg0 << 8) || true))
		arg0 += *(vm->mem + MEM_CIR_POS(ps->pc + OPCODE_SIZE + i));
	new = ft_cpy_playr(ps);
	if (opcode == FORK)
		new->pc = MEM_CIR_POS(ps->pc + (arg0 % IDX_MOD));
	else if (opcode == LFORK)
		new->pc = MEM_CIR_POS(ps->pc + arg0);
	ps->op_size = OPCODE_SIZE + DIR_SIZE(OP_TAB_INDEX(FORK));
	return (ft_next_op(ps, NO_CARRY));
}
