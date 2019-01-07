/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:09:29 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/13 13:14:08 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
** if (vm->opt & VERBOSE && !(vm->cycle % VERBOSE_DISPLAY))
**	DEBUG ? ft_printf("cycles : %d - cycle_to_die : %d -
**	nb_process : %d\n\n", vm->cycle, vm->cycle_to_die, i) : DEBUG;
*/

static void			display_opt(t_vm_mem *vm, t_ps *ps)
{
	DEBUG ? ft_printf("launching display_opt ...\n") : DEBUG;
	if (vm->opt & NCURSE)
		ft_ncurse(vm, ps);
	if (vm->opt & DUMP && vm->cycle == vm->dump)
	{
		ft_prt_mem(vm, ps);
		exit(0);
	}
	if (vm->opt & GRAPHIC && !(vm->cycle % vm->display))
		ft_prt_mem(vm, ps);
}

int					cpu(t_vm_mem *vm, t_ps *ps)
{
	int				flag;

	flag = false;
	DEBUG ? ft_printf("launching cpu ...\n") : DEBUG;
	(void)ps;
	while ((flag == false ? true : ft_one_live_ps(*(vm->ps_st))) \
						&& vm->cycle_to_die > 0)
	{
		display_opt(vm, *(vm->ps_st));
		flag = vm->cycle >= vm->cycle_to_die ? true : false;
		exec_op(vm, *(vm->ps_st));
		g_verbose == 3 ? ft_printf("It's now cycle %d\n", vm->cycle) \
								: g_verbose;
		cpu_checks(vm, *(vm->ps_st));
		vm->cycle++;
		vm->real_cycle++;
	}
	return (EXIT_SUCCESS);
}
