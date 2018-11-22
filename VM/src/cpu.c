/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:09:29 by bbichero          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2018/11/18 15:21:38 by romontei         ###   ########.fr       */
=======
/*   Updated: 2018/11/18 15:38:48 by bbichero         ###   ########.fr       */
>>>>>>> 4bae5f8... change ps from vm->ps
=======
/*   Updated: 2018/11/22 13:08:48 by bbichero         ###   ########.fr       */
>>>>>>> b1ac0c0... qwe
=======
/*   Updated: 2018/11/22 13:19:15 by romontei         ###   ########.fr       */
>>>>>>> eb16b707ad665e8aae6e0202124e55b1555c9662
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
 ** if (vm->opt & VERBOSE && !(vm->cycle % VERBOSE_DISPLAY))
 **	DEBUG ? ft_printf("cycles : %d - cycle_to_die : %d - nb_process : %d\n\n", \
 **	vm->cycle, vm->cycle_to_die, i) : DEBUG;
 */

static void			display_opt(t_vm_mem *vm)
{
	int				i;

	i = 0;
	//while (lst && ((i++) || true))
	//	lst = lst->next;
	DEBUG ? ft_printf("launching display_opt ...\n") : DEBUG;
	if (vm->opt & DUMP && vm->cycle == vm->dump)
	{
		ft_prt_mem(vm);
		exit(ft_prt_winner(vm));
	}
	if (vm->opt & GRAPHIC && !(vm->cycle % vm->display))
	{
		ft_prt_mem(vm);
		DEBUG ? ft_printf("cycles : %d - cycle_to_die : %d - nb_process \
				: %d\n\n", vm->cycle, vm->cycle_to_die, i) : DEBUG;
	}
	if (vm->opt & NCURSE && !(vm->cycle % vm->ncurse))
		ft_ncurse(vm);
}

int					cpu(t_vm_mem *vm)
{
	int				flag;
	int				i;

	i = 0;
	flag = false;
	DEBUG ? ft_printf("launching cpu ...\n") : DEBUG;
<<<<<<< HEAD
<<<<<<< HEAD
	lst_ps = ps;
=======
	ft_printf("[CPU START] PS->PLAYER => %s (%p)\n", vm->ps[i].playr, vm->ps[i]);
>>>>>>> b1ac0c0... qwe
=======
	ft_printf("[CPU START] PS->PLAYER => %s (%p)\n", vm->ps[i].playr, vm->ps[i]);
>>>>>>> eb16b707ad665e8aae6e0202124e55b1555c9662
	while ((flag == false ? true : ft_one_live_ps(vm)) && vm->cycle_to_die > 0)
	{
		if (vm->cycle % vm->cycle_to_die == 0)
			cpu_checks(vm, i);
		if (vm->check == vm->ch_decr)
			vm->check = 0;
		display_opt(vm);
		flag = vm->cycle >= vm->cycle_to_die ? true : false;
		DEBUG ? ft_printf("\nCPU => lst->playr : %s\ncycle : \
				%d\ncycle_to_die : %d\n", vm->ps[i].playr, vm->cycle, \
				vm->cycle_to_die) : DEBUG;
		exec_op(vm);
		g_verbose == 3 ? ft_printf("It's now cycle %d\n", vm->cycle) \
				   : g_verbose;
		vm->cycle++;
		vm->real_cycle++;
		i++;
	}
	return (ft_prt_winner(vm));
}
