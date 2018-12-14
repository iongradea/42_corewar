/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_sti_ldi_lldi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:47:52 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/09 15:13:52 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int					ft_aff(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;

	(void)opcode;
	DEBUG ? ft_printf("launching ft_aff ...\n") : DEBUG;
	if (!check_ocp_fmt(vm, ps, 1) && ((ps->op_size += 2) || true))
		return (ft_next_op(ps, NO_CARRY));
	arg0 = ft_get_arg(vm, ps, 0);
	ps->op_size = ft_op_size(vm, ps, 1);
	if (is_invalid_reg(vm, ps, 0, arg0))
		return (ft_next_op(ps, NO_CARRY));
	ft_printf("%c\n", ps->reg[arg0] % 256);
	return (ft_next_op(ps, NO_CARRY));
}

/*
** DEBUG ? ft_printf("launching ft_sti ...\n") : DEBUG;
*/

int					ft_sti(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;
	int				arg1;
	int				arg2;
	int				sum;
	int				i;

	(void)opcode;
	i = -1;
	sum = 0;
	if (!check_ocp_fmt(vm, ps, 3) && ((ps->op_size += 2) || true))
		return (ft_next_op(ps, NO_CARRY));
	arg0 = ft_get_arg(vm, ps, 0);
	arg1 = ft_get_arg(vm, ps, 1);
	arg2 = ft_get_arg(vm, ps, 2);
	ps->op_size = ft_op_size(vm, ps, 3);
	if (is_invalid_reg(vm, ps, 2, arg2) || is_invalid_reg(vm, ps, 0, arg0)
			|| is_invalid_reg(vm, ps, 1, arg1))
		return (ft_next_op(ps, NO_CARRY));
	sum = ft_sti_2(vm, ps, arg1, arg2);
	while (++i < REG_SIZE)
		*(vm->mem + ft_mem_cir_pos(ps->pc + (sum % IDX_MOD) + i)) =
			(char)(ps->reg[arg0] >> ((3 - i) * 8));
	ft_chg_mem_uid(vm, ps, sum, REG_SIZE);
	return (ft_next_op(ps, NO_CARRY));
}

/*
** ENLEVER LE IDX_MOD de cette fonction (pas dans le sujet 42)
*/

int					ft_ldi(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;
	int				arg1;
	int				arg2;
	int				sum;
	int				i;

	(void)opcode;
	DEBUG ? ft_printf("launching ft_ldi ...\n") : DEBUG;
	sum = 0;
	i = -1;
	if (!check_ocp_fmt(vm, ps, 3) && ((ps->op_size += 2) || true))
		return (ft_next_op(ps, NO_CARRY));
	arg0 = ft_get_arg(vm, ps, 0);
	arg1 = ft_get_arg(vm, ps, 1);
	arg2 = ft_get_arg(vm, ps, 2);
	ps->op_size = ft_op_size(vm, ps, 3);
	if (is_invalid_reg(vm, ps, 2, arg2) || is_invalid_reg(vm, ps, 0, arg0)
			|| is_invalid_reg(vm, ps, 1, arg1))
		return (ft_next_op(ps, NO_CARRY));
	sum = ft_ldi_2(vm, ps, arg1, arg2);
	while (++i < REG_SIZE && ((ps->reg[arg2] <<= 8) || true))
		ps->reg[arg2] += *(vm->mem + ft_mem_cir_pos(ps->pc \
					+ (sum % IDX_MOD) + i));
	return (ft_next_op(ps, NO_CARRY));
}

/*
** ft_lldi : same as ldi but no IDX_MOD & modifies the carry
*/

int					ft_lldi(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;
	int				arg1;
	int				arg2;
	int				sum;
	int				i;

	(void)opcode;
	DEBUG ? ft_printf("launching ft_lldi ...\n") : DEBUG;
	sum = 0;
	i = -1;
	if (!check_ocp_fmt(vm, ps, 3) && ((ps->op_size += 2) || true))
		return (ft_next_op(ps, CARRY_FALSE));
	arg0 = ft_get_arg(vm, ps, 0);
	arg1 = ft_get_arg(vm, ps, 1);
	arg2 = ft_get_arg(vm, ps, 2);
	ps->op_size = ft_op_size(vm, ps, 3);
	if (is_invalid_reg(vm, ps, 2, arg2) || is_invalid_reg(vm, ps, 0, arg0)
			|| is_invalid_reg(vm, ps, 1, arg1))
		return (ft_next_op(ps, CARRY_FALSE));
	sum = ft_lldi_2(vm, ps, arg1, arg2);
	while (++i < REG_SIZE && ((ps->reg[arg2] <<= 8) || true))
		ps->reg[arg2] += *(vm->mem + ft_mem_cir_pos(ps->pc + sum + i));
	return (ft_next_op(ps, CARRY_TRUE));
}
