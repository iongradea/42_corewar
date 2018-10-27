/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2018/10/26 19:31:16 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/vm.h"

int  ft_nb_live(t_ps *ps)
{
	int   nb_live;

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

void  ft_kill_reset_ps(t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_kill_reset_ps ...\n") : DEBUG;
	while (ps)
	{
		if (ps->live <= 0)
			ps->live = PS_DEAD;
		else
			ps->live = 0;
		ps = ps->next;
	}
}

void   ft_reset_ps(t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_reset_ps ...\n") : DEBUG;
	while (ps)
	{
		if (ps->live != PS_DEAD)
			ps->live = 0;
		ps = ps->next;
	}
}

int   ft_one_live_ps(t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_one_live_ps ...\n") : DEBUG;
	while (ps)
	{
		if (ps->live != PS_DEAD)
			return (true);
		ps = ps->next;
	}
	return (false);
}
