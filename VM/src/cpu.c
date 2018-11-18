/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:09:29 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/18 15:15:21 by romontei         ###   ########.fr       */
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

static int		ft_valid_opcode(int opcode)
{
	int			i;

	i = -1;
	while (++i < NB_OP)
		if (opcode == op_tab[i].opcode)
			return (true);
	return (false);
}

static int		ft_cycle_len(int opcode)
{
	int			i;

	i = -1;
	while (++i < NB_OP)
	{
		if (opcode == op_tab[i].opcode)
			return (op_tab[i].cycle);
	}
	return (1);
}

int					cpu(t_vm_mem *vm, t_ps *ps)
{
	t_ps			*lst_ps;
	int				flag;

	flag = false;
	lst_ps = NULL;
	DEBUG ? ft_printf("launching cpu ...\n") : DEBUG;
	lst_ps = ps;
	ft_printf("[CPU START] PS->PLAYER => %s (%p)\n", ps->playr, ps);
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
	//	exec_op(vm, lst_ps);
		while (ps && ps->cyc_len >= 0)
		{
			ft_printf("[CPU WHILE] PS->PLAYER => %s (%p)\n", ps->playr, ps);
			if (ps->cyc_len == 0)
			{
				ps->opcode = *(vm->mem + MEM_CIR_POS(ps->pc));
				ps->cyc_len = ft_cycle_len(ps->opcode);
				if (!ft_valid_opcode(ps->opcode))
				{
					ps->op_size = 1;
					return (ft_next_op(ps, NO_CARRY));
				}
				else
				{
					ft_printf("[WHILE ELSE] PS->PLAYER => %s (%p)\n", ps->playr, ps);
					if (!ft_strcmp("live", op_tab[OP_TAB_INDEX(ps->opcode)].mmemo))
					{
						vm->lives++;
						ps->live++;
						ft_printf("[EXEC OP WHILE] ps->playr = %s ps->live = %d (%p)\n", ps->playr, ps->live, ps);
						ft_printf("[LIVE TOT] vm->lives = %d ps->player = %s\n", vm->lives, ps->playr);
						ft_printf("[LIVE PLAYER] live = %d\n", ps->live);
					}
					g_verbose == 4 ? ft_printf("%s\n", \
						op_tab[OP_TAB_INDEX(lst_ps->opcode)].mmemo) : g_verbose;
					op_tab[OP_TAB_INDEX(ps->opcode)].fun(vm, ps, \
											ps->opcode);
				}
			}
			ps->cyc_len--;
			if (!ps->next)
				ft_printf("[EXEC OP END] ps -> %p\n", ps);
			ft_printf("[CPU WHILE NEXT] PS->PLAYER => %s (%p)\n", ps->playr, ps->next);
			ps = ps->next;
			if (!ps)
				ft_printf("[EXEC OP] PS -> NULL\n");
		}
		g_verbose == 3 ? ft_printf("It's now cycle %d\n", vm->cycle) \
				   : g_verbose;
		vm->cycle++;
		vm->real_cycle++;
	}
	return (ft_prt_winner(vm, ps));
}
