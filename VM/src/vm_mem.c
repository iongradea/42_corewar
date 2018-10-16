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

static int   ft_get_dist(t_ps *ps)
{
  int   code_size;
  int   nb_ps;

  code_size = 0;
  nb_ps = 0;
  while (ps)
  {
    code_size += ps->code_size;
    nb_ps++;
    ps = ps->next;
  }
  return ((MEM_SIZE - code_size) / nb_ps);
}

static void   ft_cpy_code(t_vm_mem *vm, t_ps *ps, int *j)
{
  int i;

  i = -1;
  // code starts at beginning of line (visual display)
  while (*j % MEM_LINE_LENGTH)
    (*j)--;
  ps->pc = MEM_CIR_POS(*j);
  while (++i < ps->code_size)
  {
    vm->mem_uid[(*j)] = ps->uid;
    vm->mem[(*j)++] = ps->code[i];
  }
}

t_vm_mem  *ft_new_mem(void)
{
  t_vm_mem *vm;

  if (!(vm = (t_vm_mem*)ft_memalloc(sizeof(t_vm_mem))))
    exit(ERROR_MSG("ft_new_mem : error heap allocation"));
  ft_bzero(vm->mem, MEM_SIZE);
  vm->cycle = 0;
  vm->cycle_to_die = CYCLE_TO_DIE;
  vm->ch_decr = 0;
  vm->check = 0;
  vm->opt = 0x00;
  vm->display = 0;
  vm->dump = 0;
  ft_memset(vm->mem_uid, NO_PLAYR, sizeof(vm->mem_uid));
  ft_bzero(vm->mem_color, sizeof(vm->mem_color));
  vm->mem_color_size = 0;
  vm->mem_color_ind = 0;
  vm->last_live = NO_PLAYR;
  return (vm);
}

void      add_data_vm(t_vm_mem *vm, t_ps *ps)
{
  int      j;
  int     dist;

  j = 0;
  dist = ft_get_dist(ps);
  ft_cpy_code(vm, ps, &j);
  j += dist;
  ps = ps->next;
  while (ps)
  {
    ft_cpy_code(vm, ps, &j);
    j += dist;
    ps = ps->next;
  }
}
