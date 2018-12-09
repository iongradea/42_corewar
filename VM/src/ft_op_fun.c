/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:35:08 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/08 16:44:11 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int					ft_arg_size(t_vm_mem *vm, t_ps *ps, int arg_i)
{
	DEBUG ? ft_printf("launching ft_arg_size ...\n") : DEBUG;
	if (ft_is_type(vm, ps, arg_i, T_REG))
		return (REG_SIZE);
	if (ft_is_type(vm, ps, arg_i, T_DIR))
		return (DIR_SIZE(OP_TAB_INDEX(*(vm->mem + ft_mem_cir_pos(ps->pc)))));
	if (ft_is_type(vm, ps, arg_i, T_IND))
		return (IND_SIZE);
	exit(error_msg("ft_arg_size : error unknown type"));
}

int					ft_op_size(t_vm_mem *vm, t_ps *ps, int nb_arg)
{
	int				op_size;

	if (nb_arg == 1)
		op_size = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0);
	else if (nb_arg == 2)
		op_size = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0)
			+ ft_arg_size(vm, ps, 1);
	else if (nb_arg == 3)
		op_size = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0)
			+ ft_arg_size(vm, ps, 1) + ft_arg_size(vm, ps, 2);
	else
		exit(error_msg("ft_get_op_size : error wrong nb_arg"));
	return (op_size);
}

int					ft_get_arg(t_vm_mem *vm, t_ps *ps, int arg_i)
{
	int				offset;
	int				arg;
	int				i;

	DEBUG ? ft_printf("launching ft_get_arg ...\n") : DEBUG;
	i = -1;
	arg = 0;
	offset = 0;
	if (arg_i == 0)
		offset = OPCODE_SIZE + OCP_SIZE;
	else if (arg_i == 1)
		offset = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0);
	else if (arg_i == 2)
		offset = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0) \
											+ ft_arg_size(vm, ps, 1);
	while (++i < ft_arg_size(vm, ps, arg_i) && ((arg = arg << 8) || true))
		arg += *(vm->mem + ft_mem_cir_pos(ps->pc + offset + i));
	return (arg);
}

/*
** ft_get_val is only used for binary operation functions :
** and, or and xor
** the indirect value is considered 2 bytes (as in the op.h file)
*/

int					ft_get_val(t_ps *ps, t_vm_mem *vm, int arg, int arg_i)
{
	int				val;

	val = 0;
	DEBUG ? ft_printf("launching ft_get_val ...\n") : DEBUG;
	if (ft_is_type(vm, ps, arg_i, T_REG))
		val = ps->reg[arg];
	else if (ft_is_type(vm, ps, arg_i, T_IND))
	{
		val = (unsigned char)*(vm->mem + ft_mem_cir_pos(ps->pc + arg));
		val <<= 8;
		val += (unsigned char)*(vm->mem + ft_mem_cir_pos(ps->pc + arg + 1));
		return ((short)val);
	}
	else if (ft_is_type(vm, ps, arg_i, T_DIR))
		val = arg;
	else
		exit(error_msg("ft_get_val : error unknown parameter type"));
	return (val);
}

int					ft_get_ind(t_ps *ps, t_vm_mem *vm, int arg, int idx_mod)
{
	int				val;

	DEBUG ? ft_printf("launching ft_get_ind ...\n") : DEBUG;
	val = 0;
	if (idx_mod == true)
	{
		val = *(vm->mem + ft_mem_cir_pos(ps->pc + (arg % IDX_MOD)));
		val = val << 8;
		val += *(vm->mem + ft_mem_cir_pos(ps->pc + (arg % IDX_MOD) + 1));
		return ((short)val);
	}
	else
	{
		val = *(vm->mem + ft_mem_cir_pos(ps->pc + arg));
		val = val << 8;
		val += *(vm->mem + ft_mem_cir_pos(ps->pc + arg + 1));
		return ((short)val);
	}
}
