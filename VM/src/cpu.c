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

# include "../inc/vm.h"

static void   display_opt(t_vm_mem *vm, t_ps *ps)
{
  int i;
  t_ps *lst;

  i = 0;
  lst = ps;
  while (lst && ((i++) || true))
    lst = lst->next;
  DEBUG ? ft_printf("launching display_opt ...\n") : DEBUG;
  if (vm->opt & DUMP && vm->cycle == vm->dump)
  {
    ft_prt_mem(vm, ps);
    exit(ft_prt_winner(vm, ps));
  }
  if (vm->opt & GRAPHIC && !(vm->cycle % vm->display))
  {

    ft_prt_mem(vm, ps);
    ft_printf("cycles : %d - cycle_to_die : %d - nb_process : %d\n\n", vm->cycle, vm->cycle_to_die, i);
  }
  if (vm->opt & VERBOSE && !(vm->cycle % VERBOSE_DISPLAY))
    ft_printf("cycles : %d - cycle_to_die : %d - nb_process : %d\n\n", vm->cycle, vm->cycle_to_die, i);
}

static void   cpu_checks(t_vm_mem *vm, t_ps *ps)
{
  DEBUG ? ft_printf("launching cpu_checks ...\n") : DEBUG;
  if (vm->check > vm->cycle_to_die)
  {
    DEBUG ? ft_printf("KILL_RESET - check : %d - cycle_to_die : %d\n", vm->check, vm->cycle_to_die) : DEBUG;
    ft_kill_reset_ps(ps);
    vm->check = 0;
  }
  if (ft_nb_live(ps) > NBR_LIVE)
  {
    ft_reset_ps(ps);
    DEBUG ? ft_printf("NB_LIVE - ft_nb_live(ps) : %d - NBR_LIVE : %d\n", ft_nb_live(ps), NBR_LIVE) : DEBUG;
    vm->cycle_to_die -= CYCLE_DELTA;
    vm->ch_decr = 0;
  }
  if (vm->ch_decr > MAX_CHECKS)
  {
    DEBUG ? ft_printf("MAX_CHECKS - vm->ch_decr : %d - MAX_CHECKS : %d\n", vm->ch_decr, MAX_CHECKS) : DEBUG;
    vm->cycle_to_die -= CYCLE_DELTA;
    vm->ch_decr = 0;
  }
}

int   cpu(t_vm_mem *vm, t_ps *ps)
{
  t_ps *lst;
  int flag;

  DEBUG ? ft_printf("launching cpu ...\n") : DEBUG;
  flag = false;
  lst = NULL;
  //prt_ps(ps);
  // the flag is used here to identify if the program has already passed
  // the first cycle_to_die cycle  
  while ((flag == false ? true : ft_one_live_ps(ps)) && vm->cycle_to_die > 0)
  {
    //ft_printf("cycles : %d - cycle_to_die : %d\n\n", vm->cycle, vm->cycle_to_die);
    if (!lst)
      lst = ps;
    DEBUG ? ft_printf("\nCPU => lst->playr : %s\ncycle : %d\ncycle_to_die : %d\n", lst->playr, vm->cycle, vm->cycle_to_die) : DEBUG;
    cpu_checks(vm, ps);
    exec_op(vm, lst);
    display_opt(vm, ps);
    flag = vm->cycle >= vm->cycle_to_die ? true : false;
    lst = lst->next;
    vm->check++;
    vm->ch_decr++;
    vm->cycle++;
  }
  //prt_ps(ps);
  //prt_vm(vm);
  //ft_printf("CPU : %d\n", ft_one_live_ps(ps));
  return (ft_prt_winner(vm, ps));
}
