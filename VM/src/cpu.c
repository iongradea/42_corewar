/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:09:29 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/18 15:21:38 by romontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
 ** if (vm->opt & VERBOSE && !(vm->cycle % VERBOSE_DISPLAY))
 **	DEBUG ? ft_printf("cycles : %d - cycle_to_die : %d - nb_process : %d\n\n", \
 **	vm->cycle, vm->cycle_to_die, i) : DEBUG;
 */

static void			display_opt(t_vm_mem *vm, t_ps *ps)
{
	int				i;
	t_ps			*lst;

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
		DEBUG ? ft_printf("cycles : %d - cycle_to_die : %d - nb_process \
				: %d\n\n", vm->cycle, vm->cycle_to_die, i) : DEBUG;
	}
	if (vm->opt & NCURSE && !(vm->cycle % vm->ncurse))
		ft_ncurse(vm);
}

int					cpu(t_vm_mem *vm, t_ps *ps)
{
	t_ps			*lst_ps;
	int				flag;

	flag = false;
	lst_ps = NULL;
	DEBUG ? ft_printf("launching cpu ...\n") : DEBUG;
	lst_ps = ps;
	while ((flag == false ? true : ft_one_live_ps(vm)) && vm->cycle_to_die > 0)
	{
		if (!ps)
			ps = lst_ps;
		if (vm->cycle % vm->cycle_to_die == 0)
			cpu_checks(vm, ps);
		if (vm->check == vm->ch_decr)
			vm->check = 0;
		display_opt(vm, ps);
		flag = vm->cycle >= vm->cycle_to_die ? true : false;
		DEBUG ? ft_printf("\nCPU => lst->playr : %s\ncycle : \
				%d\ncycle_to_die : %d\n", lst_ps->playr, vm->cycle, \
				vm->cycle_to_die) : DEBUG;
		exec_op(vm, lst_ps);
		g_verbose == 3 ? ft_printf("It's now cycle %d\n", vm->cycle) \
				   : g_verbose;
		vm->cycle++;
		vm->real_cycle++;
	}
	return (ft_prt_winner(vm, ps));
}
