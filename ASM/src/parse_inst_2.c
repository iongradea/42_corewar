/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2013/11/06 14:44:35 by iongradea        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int 	ft_ch_opcode(char *str)
{
	int i;

	i = -1;
  DEBUG ? ft_printf("launching ft_ch_opcode ...\n") : DEBUG;
	while (++i < NB_OP)
	{
		if (!ft_strcmp(str, op_tab[i].mmemo))
			return (true);
	}
	return (false);
}

int		ft_ret_opcode(char *str)
{
	int i;

	i = -1;
  DEBUG ? ft_printf("launching ft_ret_opcode ...\n") : DEBUG;
	while (++i < NB_OP)
	{
		if (!ft_strcmp(str, op_tab[i].mmemo))
			return (i);
	}
	return (ERROR);
}

int		ft_ch_err_lab(char *str)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(str);
  DEBUG ? ft_printf("launching ft_ch_err_lab ...\n") : DEBUG;
	while (++i < len)
	{
		if (str[i] == LABEL_CHAR && i != len - 1)
			return (true);
	}
	return (false);
}

int 		ft_ch_rm_lab_c(char **str)
{
	int len;

	len = ft_strlen(*str);
  DEBUG ? ft_printf("launching ft_ch_rm_lab_c ...\n") : DEBUG;
	if ((*str)[len - 1] == LABEL_CHAR)
	{
		(*str)[len - 1] = ' ';
		return (true);
	}
	return (false);
}
