/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:40:42 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/08 17:13:08 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int			ft_nb_live(t_ps *ps)
{
	int		nb_live;

	DEBUG ? ft_printf("launching ft_nb_live ...\n") : DEBUG;
	nb_live = 0;
	while (ps)
	{
		if (ps->live > 0)
			nb_live += ps->live;
		ps = ps->next;
	}
	return (nb_live);
}

void		ft_kill_reset_ps(t_vm_mem *vm)
{
	t_ps *tmp;
	t_ps *ps;

	DEBUG ? ft_printf("launching ft_kill_reset_ps ...\n") : DEBUG;
	ps = *(vm->ps_st);
	vm->playr_live[0] = 0;
	vm->playr_live[1] = 0;
	vm->playr_live[2] = 0;
	vm->playr_live[3] = 0;
	while (ps)
	{
		tmp = NULL;
		if (ps->live <= 0)
		{
			g_verbose == 5 ? ft_printf("Le joueur %d(%s) viens de mourrir \
									...\n", ps->uid, ps->playr) : g_verbose;
			ps->live = PS_DEAD;
			if (ps->prev && ps->next && ps->prev->prev && ps->prev->prev->prev \
				&& ps->prev->prev->prev->prev)
			{
				tmp = ps->next;
				ps->next->prev = ps->prev;
				ps->prev->next = ps->next;
				ft_free_ps(ps);
			}
		}
		else
			ps->live = 0;
		ps = tmp == NULL ? ps->next : tmp;
	}
}

int			ft_one_live_ps(t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_one_live_ps ...\n") : DEBUG;
	while (ps)
	{
		if (ps->live != PS_DEAD)
		{
			g_verbose == 2 ? ft_printf("Le joueur %d(%s) est en vie \
								...\n", ps->uid, ps->playr) : g_verbose;
			return (true);
		}
		ps = ps->next;
	}
	return (false);
}

int			ft_mem_cir_pos(int pos)
{
	if (((pos) % MEM_SIZE) < 0)
		return (((pos) % MEM_SIZE) + MEM_SIZE);
	else
		return (((pos) % MEM_SIZE));
}
