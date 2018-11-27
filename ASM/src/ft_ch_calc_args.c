/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/27 17:05:53 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int				ch_all_inst(t_inst *inst)
{
	int			i;
	int			j;
	t_inst		*tmp;

	i = -1;
	j = -1;
	tmp = inst;
	DEBUG ? ft_printf("launching ch_all_inst ...\n") : DEBUG;
	while (tmp)
	{
		if (ft_is_valid_opcode(tmp->opcode))
		{
			if (!ch_one_inst(tmp, inst))
			{
				error_msg("Error .s file at line : ");
				error_msg(tmp->line);
				exit(error_msg("\n"));
			}
		}
		tmp = tmp->n;
	}
	return (true);
}

int				calc_all_size(t_inst *inst)
{
	t_inst		*tmp;
	int			size;

	tmp = inst;
	size = 0;
	DEBUG ? ft_printf("launching calc_all_size ...\n") : DEBUG;
	while (tmp)
	{
		tmp->size = calc_one_inst_size(tmp);
		tmp = tmp->n;
	}
	tmp = inst;
	while (tmp)
	{
		if (tmp->size != UNDEFINED)
			size += tmp->size;
		tmp = tmp->n;
	}
	return (size);
}

int				ft_is_lab(char *arg)
{
	int			len;

	len = ft_strlen(arg);
	if ((*arg == DIRECT_CHAR && len > 2 && *(arg + 1) == LABEL_CHAR)
		|| (*arg == LABEL_CHAR && len > 1))
		return (true);
	return (false);
}
