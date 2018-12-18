/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/12/17 14:38:39 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int		protect_define(void)
{
	DEBUG ? ft_printf("launching protect_define ...\n") : DEBUG;
	if (MEM_SIZE % 1024 != 0 || MEM_SIZE > 101024)
		return (0);
	if (REG_NUMBER != 16)
		return (0);
	if (REG_SIZE != 4)
		return (0);
	if (MAX_PLAYERS != 4)
		return (0);
	if (MAX_CHECKS != 9)
		return (0);
	if (NBR_LIVE != 21)
		return (0);
	if (CYCLE_DELTA < 0 || CYCLE_DELTA > CYCLE_TO_DIE)
		return (0);
	return (1);
}

/*
** ft_new_mem	= Instantiate VM
** ft_parse_opt = parse cli arg
** get_playr	= check argument players
** ft_main_debug(vm, ps);
** ft_prt_mem(vm, ps);
*/

int				main(int ac, char **av)
{
	t_ps		*ps;
	t_vm_mem	*vm;

	ps = NULL;
	if (ac < 2)
		exit(ft_usage());
	if (!protect_define())
		exit(error_msg("Invalid define, please check 'inc/vm.h'"));
	vm = ft_new_mem();
	vm->ps_st = &ps;
	ft_parse_opt(ac, av, vm);
	get_playr(vm, &ps, ac, av);
	add_data_vm(vm, ps);
	cpu(vm, ps);
	ft_prt_winner(vm, ps);
	if (vm->opt & NCURSE)
	{
		while (42)
			;
	}
	free(vm);
	ft_free_all_ps(ps);
	exit(EXIT_SUCCESS);
}
