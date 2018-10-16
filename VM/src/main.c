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

int main(int ac, char **av)
{
  int   fd;
  t_ps  *ps;
  t_vm_mem *vm;

  fd = 0;
  ps = NULL;
  if (ac < 3)
    exit(ft_usage());
  vm = ft_new_mem();
  ft_parse_opt(ac, av, vm);
  get_playr(fd, &ps, ac, av);
  add_data_vm(vm, ps);
  cpu(vm, ps);
  // DEBUGGING
  //ft_main_debug(vm, ps);
  //ft_prt_mem(vm, ps);
  exit(EXIT_SUCCESS);
}
