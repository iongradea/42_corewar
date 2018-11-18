/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:40:42 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/18 15:10:45 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int			ft_nb_live(t_vm_mem *vm)
{
	int		nb_live;
	int		i;

	DEBUG ? ft_printf("launching ft_nb_live ...\n") : DEBUG;
	i = 0;
	nb_live = 0;
	while (i < vm->nb_players)
	{
		if (vm->ps[i].live > 0)
			nb_live += vm->ps[i].live;
		i++;
	}
	return (nb_live);
}

void		ft_kill_reset_ps(t_vm_mem *vm)
{
	int	i;

	i = 0;
	DEBUG ? ft_printf("launching ft_kill_reset_ps ...\n") : DEBUG;
	while (i < vm->nb_players)
	{
		if (vm->ps[i].live <= 0)
		{
			g_verbose == 5 ? ft_printf("Le joueur %d(%s) viens de mourrir \
									...\n", vm->ps[i].uid, vm->ps[i].playr) : g_verbose;
			vm->ps[i].live = PS_DEAD;
		}
		else
			vm->ps[i].live = 0;
		i++;
	}
}

void		ft_reset_ps(t_vm_mem *vm)
{
	int	i;

	i = 0;
	DEBUG ? ft_printf("launching ft_reset_ps ...\n") : DEBUG;
	while (i < vm->nb_players)
	{
		if (vm->ps[i].live != PS_DEAD)
			vm->ps[i].live = 0;
		i++;
	}
}

int			ft_one_live_ps(t_vm_mem *vm)
{
	int	i;

	i = 0;
	DEBUG ? ft_printf("launching ft_one_live_ps ...\n") : DEBUG;
	while (i < vm->nb_players)
	{
		if (vm->ps[i].live != PS_DEAD)
		{
			g_verbose == 2 ? ft_printf("Le joueur %d(%s) est en vie \
								...\n", vm->ps[i].uid, vm->ps[i].playr) : g_verbose;
			return (true);
		}
		i++;
	}
	return (false);
}
