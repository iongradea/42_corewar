/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2018/10/25 15:49:52 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

void  prt_op(void)
{
	int i;

	i = -1;
	ft_printf("T_DIR : %03b\nT_IND : %03b\nT_REG : %03b\n", T_DIR, T_IND, T_REG);
	while (++i < 16)
		ft_printf("%- 6s : %d => [%03b, %03b, %03b]\n", op_tab[i].mmemo,
				op_tab[i].nb_param, op_tab[i].param[0], op_tab[i].param[1],
				op_tab[i].param[2]);
}

void  prt_ps(t_ps *ps)
{
	int i;

	DEBUG ? ft_printf("launching prt_ps ...\n") : DEBUG;
	while (ps)
	{
		i = -1;
		ft_printf("playr : %s\nuid : %d\n", ps->playr, ps->uid);
		print_memory(ps->code, ps->code_size);
		ft_printf("code_size : %d\n", ps->code_size);
		while (++i < REG_NUMBER)
			ft_printf("reg[%d] : %d\n", i, ps->reg[i]);
		ft_printf("pc : %d\ncarry : %d\nop_size : %d\nlive : %d\n\n", ps->pc, ps->carry, ps->op_size, ps->live);
		ps = ps->next;
	}
}

void  prt_vm(t_vm_mem *vm)
{
	print_memory(vm->mem, MEM_SIZE);
	ft_printf("cycle : %d\ncycle_to_die : %d\nch_decr : %d\n\
			check : %d\nopt : %d\ndump : %d\ndisplay : %d\n", vm->cycle, vm->cycle_to_die,
			vm->ch_decr, vm->check, vm->opt, vm->dump, vm->display);
	ft_printf("last_live : %d\n", vm->last_live);
}

void prt_mem_uid(t_vm_mem *vm)
{
	int i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % MEM_LINE_LENGTH == 0)
			ft_printf("\n");
		ft_printf("%d ", vm->mem_uid[i]);
	}
}

int ft_main_debug(t_vm_mem *vm, t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_main_debug ...\n") : DEBUG;

	DEBUG ? ft_printf("\n\n") : DEBUG;
	DEBUG ? prt_ps(ps) : DEBUG;
	DEBUG ? ft_printf("\n\n") : DEBUG;
	DEBUG ? prt_vm(vm) : DEBUG;
	//ft_bin(vm, ps, XOR);
	//ft_add_sub(vm, ps, SUB);
	//ft_live(vm, ps);
	//ft_ld(vm, ps, LLD);
	//ft_st(vm, ps);
	//ft_zjmp(vm, ps);
	//ft_fork(vm, ps, LFORK);
	//ft_aff(vm, ps);
	//ft_sti(vm, ps);
	//ft_ldi(vm, ps);
	//ft_lldi(vm, ps);
	DEBUG ? ft_printf("\n\n") : DEBUG;
	DEBUG ? prt_ps(ps) : DEBUG;
	DEBUG ? ft_printf("\n\n") : DEBUG;
	DEBUG ? prt_vm(vm) : DEBUG;
	DEBUG ? ft_printf("\n\n") : DEBUG;
	DEBUG ? prt_mem_uid(vm) : DEBUG;
	DEBUG ? ft_printf("\n\n") : DEBUG;

	/*
	   ft_printf("\ng_color[0] : %s%s%s xxx\n", g_color[1], "tst", EOC);

	 *int i = -1;
	 while (++i < 10)
	 ft_printf("c :%x\n", g_color[0][i]);*/
	return (EXIT_SUCCESS);
}
