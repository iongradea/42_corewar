/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:44:20 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/01 18:46:43 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void		prt_op(void)
{
	int		i;

	i = -1;
	ft_printf("T_DIR : %03b\nT_IND : %03b\nT_REG : %03b\n", T_DIR, T_IND, \
																	T_REG);
	while (++i < 16)
		ft_printf("%- 6s : %d => [%03b, %03b, %03b]\n", g_op_tab[i].mmemo, \
				g_op_tab[i].nb_param, g_op_tab[i].param[0], \
				g_op_tab[i].param[1], g_op_tab[i].param[2]);
}

void		prt_ps(t_ps *ps)
{
	int		i;

	DEBUG ? ft_printf("launching prt_ps ...\n") : DEBUG;
	while (ps)
	{
		i = -1;
		ft_printf("\nplayr : %s\nuid : %d\nps_uid : %d\n", ps->playr, ps->uid, \
														ps->ps_uid);
		print_memory(ps->code, ps->code_size);
		ft_printf("code_size : %d\n", ps->code_size);
		while (++i < REG_NUMBER)
			ft_printf("reg[%d] : %d\n", i, ps->reg[i]);
		ft_printf("pc : %d\ncarry : %d\nop_size : %d\nlive : %d\n", \
								ps->pc, ps->carry, ps->op_size, ps->live);
		ft_printf("ps->next : %p\n\n", ps->next);
		ps = ps->next;
	}
}

void		prt_vm(t_vm_mem *vm)
{
	print_memory(vm->mem, MEM_SIZE);
	ft_printf("cycle : %d\ncycle_to_die : %d\nch_decr : %d\n\
			check : %d\nopt : %d\ndump : %d\ndisplay : %d\n", vm->cycle, \
														vm->cycle_to_die,
			vm->ch_decr, vm->check, vm->opt, vm->dump, vm->display);
	ft_printf("last_live : %d\n", vm->last_live);
}

void		prt_mem_uid(t_vm_mem *vm)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % MEM_LINE_LENGTH == 0)
			ft_printf("\n");
		ft_printf("%d ", vm->mem_uid[i]);
	}
}

int			protect_define(void)
{
	DEBUG ? ft_printf("launching protect_define ...\n") : DEBUG;
	if (MEM_SIZE % 1024 != 0 || MEM_SIZE > 101024)
		return (0);
	if (REG_NUMBER != 16)
		return (0);
	if (REG_SIZE != 4)
		return (0);
	if (MAX_PLAYERS != 4)
		return (0);
	if (MAX_CHECKS != 9)
		return (0);
	if (NBR_LIVE != 21)
		return (0);
	if (CYCLE_DELTA < 0 || CYCLE_DELTA > CYCLE_TO_DIE)
		return (0);
	return (1);
}
