/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 19:23:49 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int			ft_is_reg(char *str)
{
	if (*str == 'r')
		return (true);
	return (false);
}

int			ft_is_ind(char *str)
{
	if ((*str >= '0' && *str <= '9') || *str == '-')
		return (true);
	if (*str == LABEL_CHAR)
		return (true);
	return (false);
}

/*
**	works also for labels because they are DIR (when start with '%:')
*/

int			ft_is_dir(char *str)
{
	if (*str == DIRECT_CHAR)
		return (true);
	return (false);
}

int			ft_arg_size(char *arg, int opcode)
{
	DEBUG ? ft_printf("launching ft_arg_size ...\n") : DEBUG;
	if (ft_is_reg(arg))
		return (REG_SIZE);
	if (ft_is_ind(arg))
		return (IND_SIZE);
	if (ft_is_dir(arg))
		return (DIR_SIZE(opcode));
	exit(error_msg("arg_size error\n"));
}

int			calc_one_inst_size(t_inst *tmp)
{
	int		size;

	size = 0;
	DEBUG ? ft_printf("launching calc_one_inst_size ...\n") : DEBUG;
	if (!ft_is_valid_opcode(tmp->opcode))
		return (UNDEFINED);
	size++;
	if (op_tab[OP_TAB_INDEX(tmp->opcode)].ocp_param)
		size++;
	if (tmp->args[ARG_INDEX(0)])
		size += ft_arg_size(tmp->args[ARG_INDEX(0)], tmp->opcode);
	if (tmp->args[ARG_INDEX(1)])
		size += ft_arg_size(tmp->args[ARG_INDEX(1)], tmp->opcode);
	if (tmp->args[ARG_INDEX(2)])
		size += ft_arg_size(tmp->args[ARG_INDEX(2)], tmp->opcode);
	return (size);
}
