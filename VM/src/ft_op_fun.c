/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2013/11/06 14:21:46 by igradea              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int  ft_arg_size(t_vm_mem *vm, t_ps *ps, int arg_i)
{
  DEBUG ? ft_printf("launching ft_arg_size ...\n") : DEBUG;
  if (ft_is_type(vm, ps, arg_i, T_REG))
    return (REG_SIZE);
  if (ft_is_type(vm, ps, arg_i, T_DIR))
    return (DIR_SIZE(OP_TAB_INDEX(*(vm->mem + MEM_CIR_POS(ps->pc)))));
  if (ft_is_type(vm, ps, arg_i, T_IND))
    return (IND_SIZE);
  exit(ERROR_MSG("ft_arg_size : error unknown type"));
}

int  ft_op_size(t_vm_mem *vm, t_ps *ps, int nb_arg)
{
  int op_size;

  if (nb_arg == 1)
    op_size = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0);
  else if (nb_arg == 2)
    op_size = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0)
    + ft_arg_size(vm, ps, 1);
  else if (nb_arg == 3)
    op_size = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0)
    + ft_arg_size(vm, ps, 1) + ft_arg_size(vm, ps, 2);
  else
    exit(ERROR_MSG("ft_get_op_size : error wrong nb_arg"));
  return (op_size);
}

unsigned int  ft_get_arg(t_vm_mem *vm, t_ps *ps, int arg_i)
{
  int           offset;
  unsigned int  arg;
  int           i;

  DEBUG ? ft_printf("launching ft_get_arg ...\n") : DEBUG;
  i = -1;
  arg = 0;
  offset = 0;
  if (arg_i == 0)
    offset = OPCODE_SIZE + OCP_SIZE;
  else if (arg_i == 1)
    offset = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0);
  else if (arg_i == 2)
    offset = OPCODE_SIZE + OCP_SIZE + ft_arg_size(vm, ps, 0)
    + ft_arg_size(vm, ps, 1);
  while (++i < ft_arg_size(vm, ps, arg_i) && ((arg = arg << 8) || true))
    arg += *(vm->mem + MEM_CIR_POS(ps->pc + offset + i));
  return (arg);
}

unsigned int ft_get_val(t_ps *ps, t_vm_mem *vm, unsigned int arg,
  int arg_i)
{
  unsigned int val;

  val = 0;
  DEBUG ? ft_printf("launching ft_get_val ...\n") : DEBUG;
  if (ft_is_type(vm, ps, arg_i, T_REG))
    val = ps->reg[arg];
  else if (ft_is_type(vm, ps, arg_i, T_IND))
    val = *(vm->mem + MEM_CIR_POS(ps->pc + arg));
  else if (ft_is_type(vm, ps, arg_i, T_DIR))
    val = arg;
  else
    exit(ERROR_MSG("ft_get_val : error unknown parameter type"));
  return (val);
}
