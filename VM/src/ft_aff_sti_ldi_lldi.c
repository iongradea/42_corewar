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

int   ft_aff(t_vm_mem *vm, t_ps *ps, int opcode)
{
  unsigned int  arg0;

  (void)opcode;
  DEBUG ? ft_printf("launching ft_aff ...\n") : DEBUG;
  if (!check_ocp_fmt(vm, ps, 1) && ((++ps->op_size) || true))
    return (ft_next_op(ps, NO_CARRY));
  arg0 = ft_get_arg(vm, ps, 0);
  ps->op_size = ft_op_size(vm, ps, 1);
  if (IS_INVALID_REG(vm, ps, 0, arg0))
    return (ft_next_op(ps, NO_CARRY));
  // DEBUGGING
  //ps->reg[1] = 42;
  //ft_printf("HERRRRE\n");
  ft_printf("%c", ps->reg[arg0] % 256);
  return (ft_next_op(ps, NO_CARRY));
}

int   ft_sti(t_vm_mem *vm, t_ps *ps, int opcode)
{
  unsigned int arg0;
  unsigned int arg1;
  unsigned int arg2;
  unsigned int sum;
  int          i;

  (void)opcode;
  DEBUG ? ft_printf("launching ft_sti ...\n") : DEBUG;
  i = -1;
  sum = 0;
  if (!check_ocp_fmt(vm, ps, 3) && ((++ps->op_size) || true))
    return (ft_next_op(ps, NO_CARRY));
  arg0 = ft_get_arg(vm, ps, 0);
  arg1 = ft_get_arg(vm, ps, 1);
  arg2 = ft_get_arg(vm, ps, 2);
  ps->op_size = ft_op_size(vm, ps, 3);
  if (IS_INVALID_REG(vm, ps, 2, arg2) || IS_INVALID_REG(vm, ps, 0, arg0)
  || IS_INVALID_REG(vm, ps, 1, arg1))
    return (ft_next_op(ps, NO_CARRY));
  //DEBUGGING
  //ps->reg[1] = 0xff01;
  //ps->reg[2] = 5;
  //ps->reg[3] = 3;
  sum = ft_is_type(vm, ps, 1, T_REG) ? ps->reg[arg1] : arg1;
  sum += ft_is_type(vm, ps, 2, T_REG) ? ps->reg[arg2] : arg2;
  // DEBUGGING
  //ft_printf("arg0 : %d - arg1 : %d - arg2 : %d - sum : %d\n", arg0, arg1, arg2, sum);
  while (++i < (int)sizeof(unsigned int))
    *(vm->mem + MEM_CIR_POS(ps->pc + sum + i)) =
    (char)(ps->reg[arg0] >> ((3 - i) * 8));
  ft_chg_mem_uid(vm, ps, sum, sizeof(unsigned int));
  return (ft_next_op(ps, NO_CARRY));
}

int   ft_ldi(t_vm_mem *vm, t_ps *ps, int opcode)
{
  unsigned int arg0;
  unsigned int arg1;
  unsigned int arg2;
  unsigned int sum;
  int          i;

  (void)opcode;
  DEBUG ? ft_printf("launching ft_ldi ...\n") : DEBUG;
  sum = 0;
  i = -1;
  if (!check_ocp_fmt(vm, ps, 3) && ((++ps->op_size) || true))
    return (ft_next_op(ps, NO_CARRY));
  arg0 = ft_get_arg(vm, ps, 0);
  arg1 = ft_get_arg(vm, ps, 1);
  arg2 = ft_get_arg(vm, ps, 2);
  ps->op_size = ft_op_size(vm, ps, 3);
  if (IS_INVALID_REG(vm, ps, 2, arg2) || IS_INVALID_REG(vm, ps, 0, arg0)
  || IS_INVALID_REG(vm, ps, 1, arg1))
    return (ft_next_op(ps, NO_CARRY));
  // DEBUGGING
  //ps->reg[arg0] = 3;
  //ps->reg[arg1] = 5;
  sum = ft_is_type(vm, ps, 1, T_REG) ? ps->pc + (ps->reg[arg0] % IDX_MOD) :
    ps->pc + (arg0 % IDX_MOD);
  sum += ft_is_type(vm, ps, 1, T_REG) ? ps->reg[arg1] : arg1;
  // DEBUGGING
  //ft_printf("arg0 : %d - arg1 : %d - arg2 : %d - sum : %d\n", arg0, arg1, arg2, sum);
  while (++i < (int)sizeof(unsigned int) && ((ps->reg[arg2] <<= 8) || true))
    ps->reg[arg2] += *(vm->mem + MEM_CIR_POS(ps->pc + (sum % IDX_MOD) + i));
  return (ft_next_op(ps, NO_CARRY));
}

/*
* ft_lldi : same as ldi but no IDX_MOD & modifies the carry
*/

int   ft_lldi(t_vm_mem *vm, t_ps *ps, int opcode)
{
  unsigned int arg0;
  unsigned int arg1;
  unsigned int arg2;
  unsigned int sum;
  int          i;

  (void)opcode;
  DEBUG ? ft_printf("launching ft_lldi ...\n") : DEBUG;
  sum = 0;
  i = -1;
  if (!check_ocp_fmt(vm, ps, 3) && ((++ps->op_size) || true))
    return (ft_next_op(ps, CARRY_FALSE));
  arg0 = ft_get_arg(vm, ps, 0);
  arg1 = ft_get_arg(vm, ps, 1);
  arg2 = ft_get_arg(vm, ps, 2);
  ps->op_size = ft_op_size(vm, ps, 3);
  if (IS_INVALID_REG(vm, ps, 2, arg2) || IS_INVALID_REG(vm, ps, 0, arg0)
  || IS_INVALID_REG(vm, ps, 1, arg1))
    return (ft_next_op(ps, CARRY_FALSE));
  // DEBUGGING
  //ps->reg[arg0] = 3;
  //ps->reg[arg1] = 5;
  sum = ft_is_type(vm, ps, 1, T_REG) ? ps->pc + ps->reg[arg0] :
    ps->pc + arg0;
  sum += ft_is_type(vm, ps, 1, T_REG) ? ps->reg[arg1] : arg1;
  // DEBUGGING
  //ft_printf("arg0 : %d - arg1 : %d - arg2 : %d - sum : %d\n", arg0, arg1, arg2, sum);
  while (++i < (int)sizeof(unsigned int) && ((ps->reg[arg2] <<= 8) || true))
    ps->reg[arg2] += *(vm->mem + MEM_CIR_POS(ps->pc + sum + i));
  return (ft_next_op(ps, CARRY_TRUE));
}
