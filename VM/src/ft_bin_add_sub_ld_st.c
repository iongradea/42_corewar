/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_add_sub_ld_st.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:52:17 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/08 16:48:03 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
** Différents cases for using the function (AND, OR, XOR)
** AND, OR and XOR all set the carry to one
** NB : HERE CONSIDERED OPCODE VALID, TO BE TESTED BEFORE !
** DEBUG ? ft_printf("launching ft_bin ...\n") : DEBUG;
*/

int					ft_bin(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int	arg0;
	int	arg1;
	int	arg2;

	if (!check_ocp_fmt(vm, ps, 3) && ((++ps->op_size) || true))
		return (ft_next_op(ps, CARRY_FALSE));
	arg0 = ft_get_arg(vm, ps, 0);
	arg1 = ft_get_arg(vm, ps, 1);
	arg2 = ft_get_arg(vm, ps, 2);
	ps->op_size = ft_op_size(vm, ps, 3);
	if (IS_INVALID_REG(vm, ps, 2, arg2) || IS_INVALID_REG(vm, ps, 0, arg0)
			|| IS_INVALID_REG(vm, ps, 1, arg1))
		return (ft_next_op(ps, CARRY_FALSE));
	if (opcode == AND)
		ps->reg[arg2] = ft_get_val(ps, vm, arg0, 0) & ft_get_val(ps, vm, \
																arg1, 1);
	else if (opcode == OR)
		ps->reg[arg2] = ft_get_val(ps, vm, arg0, 0) | ft_get_val(ps, vm, \
																arg1, 1);
	else if (opcode == XOR)
		ps->reg[arg2] = ft_get_val(ps, vm, arg0, 0) ^ ft_get_val(ps, vm, \
																arg1, 1);
	else
		exit(ERROR_MSG("ft_bin : error wrong opcode"));
	return (ft_next_op(ps, CARRY_TRUE));
}

int					ft_add_sub(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int	arg0;
	int	arg1;
	int	arg2;

	DEBUG ? ft_printf("launching ft_add_sub ...\n") : DEBUG;
	if (!check_ocp_fmt(vm, ps, 3) && ((++ps->op_size) || true))
		return (ft_next_op(ps, CARRY_FALSE));
	arg0 = ft_get_arg(vm, ps, 0);
	arg1 = ft_get_arg(vm, ps, 1);
	arg2 = ft_get_arg(vm, ps, 2);
	ps->op_size = ft_op_size(vm, ps, 3);
	if (IS_INVALID_REG(vm, ps, 0, arg0) || IS_INVALID_REG(vm, ps, 1, arg1)
			|| IS_INVALID_REG(vm, ps, 2, arg2))
		return (ft_next_op(ps, CARRY_FALSE));
	if (opcode == ADD)
		ps->reg[arg2] = ps->reg[arg0] + ps->reg[arg1];
	else if (opcode == SUB)
		ps->reg[arg2] = ps->reg[arg0] - ps->reg[arg1];
	else
		exit(ERROR_MSG("ft_add_sub : error wrong opcode"));
	return (ft_next_op(ps, CARRY_TRUE));
}

/*
** ENLEVER IDX_MOD (pas dans le sujet 42)
*/

int					ft_ld(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;
	int				arg1;
	int				arg_ind;
	int				i;

	DEBUG ? ft_printf("launching ft_ld ...\n") : DEBUG;
	i = -1;
	if (!check_ocp_fmt(vm, ps, 2) && ((++ps->op_size) || true))
		return (ft_next_op(ps, CARRY_FALSE));
	arg0 = ft_is_type(vm, ps, 0, T_IND) ? (short)ft_get_arg(vm, ps, 0) : \
											ft_get_arg(vm, ps, 0);
	arg1 = ft_get_arg(vm, ps, 1);
	arg_ind = (opcode == LD && ft_is_type(vm, ps, 0, T_IND)) ? \
												(arg0 % IDX_MOD) : arg0;
	ps->op_size = ft_op_size(vm, ps, 2);
	if (IS_INVALID_REG(vm, ps, 1, arg1))
		return (ft_next_op(ps, CARRY_FALSE));
	if (ft_is_type(vm, ps, 0, T_DIR))
		ps->reg[arg1] = arg_ind;
	else if (ft_is_type(vm, ps, 0, T_IND))
		while (++i < (int)sizeof(int) && ((*(ps->reg + arg1) <<= 8) || true))
			ps->reg[arg1] += *(vm->mem + ft_mem_cir_pos(ps->pc + arg_ind + i));
	return (ft_next_op(ps, CARRY_TRUE));
}

int					ft_st(t_vm_mem *vm, t_ps *ps, int opcode)
{
	int				arg0;
	int				arg1;
	int				i;

	(void)opcode;
	DEBUG ? ft_printf("launching ft_st ...\n") : DEBUG;
	i = -1;
	if (!check_ocp_fmt(vm, ps, 2) && ((++ps->op_size) || true))
		return (ft_next_op(ps, NO_CARRY));
	arg0 = ft_get_arg(vm, ps, 0);
	arg1 = ft_is_type(vm, ps, 1, T_IND) ? (short)ft_get_arg(vm, ps, 1) : \
											ft_get_arg(vm, ps, 1);
	ps->op_size = ft_op_size(vm, ps, 2);
	if (IS_INVALID_REG(vm, ps, 0, arg0) || IS_INVALID_REG(vm, ps, 1, arg1))
		return (ft_next_op(ps, NO_CARRY));
	if (ft_is_type(vm, ps, 1, T_REG))
		ps->reg[arg1] = ps->reg[arg0];
	else if (ft_is_type(vm, ps, 1, T_IND))
	{
		while (++i < (int)sizeof(int))
			*(vm->mem + ft_mem_cir_pos(ps->pc + (arg1 % IDX_MOD) + i)) =
				(unsigned char)(ps->reg[arg0] >> ((3 - i) * 8));
		ft_chg_mem_uid(vm, ps, arg1 % IDX_MOD, sizeof(int));
	}
	return (ft_next_op(ps, NO_CARRY));
}
