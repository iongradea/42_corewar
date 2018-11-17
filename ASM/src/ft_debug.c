/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 18:54:30 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

void				prt_inst(t_inst *inst)
{
	t_inst			*tmp;

	tmp = inst;
	DEBUG ? ft_printf("launching prt_inst ...\n") : DEBUG;
	while (tmp)
	{
		ft_printf("prt_inst - line : %s\n", tmp->line);
		ft_printf("label : %s\n", tmp->label);
		ft_printf("opcode : %x\n", tmp->opcode);
		ft_printf("arg1 : %s\narg2 : %s\narg3 : %s\narg4 : %s\n", \
					tmp->args[0], tmp->args[1], tmp->args[2], tmp->args[3]);
		ft_printf("size : %d\n", tmp->size);
		ft_printf("ocp : %08b\np1 : %d\np2 : %d\np3 : %d\n", tmp->ocp, \
								tmp->param[0], tmp->param[1], tmp->param[2]);
		tmp = tmp->n;
	}
}

void				prt_one_inst(t_inst *inst)
{
	t_inst			*tmp;

	tmp = inst;
	DEBUG ? ft_printf("launching prt_one_inst ...\n") : DEBUG;
	ft_printf("label : %s\n", tmp->label);
	ft_printf("opcode : %x\n", tmp->opcode);
	ft_printf("arg1 : %s\narg2 : %s\narg3 : %s\narg4 : %s\n", tmp->args[0], \
			tmp->args[1], tmp->args[2], tmp->args[3]);
	ft_printf("size : %d\n", tmp->size);
	ft_printf("ocp : %08b\np1 : %d\np2 : %d\np3 : %d\n", tmp->ocp, \
							tmp->param[0], tmp->param[1], tmp->param[2]);
}

void				prt_tab(char **tab)
{
	int				i;

	i = -1;
	while (tab[++i])
		ft_printf("tab[%d] : %s\n", i, tab[i]);
}
