/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 18:49:52 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int			ft_is_valid_reg(char *arg)
{
	int				n;
	int				i;
	int				len;

	n = 0;
	i = 0;
	len = ft_strlen(arg);
	DEBUG ? ft_printf("launching ft_is_valid_reg ...\n") : DEBUG;
	if (*arg == REGISTER_CHAR)
	{
		while (++i < len)
			if (arg[i] < '0' && arg[i] > '9')
				return (false);
		n = ft_atoi(arg + 1);
		if (n < 1 && n > REG_NUMBER)
			return (false);
		return (true);
	}
	return (false);
}

static int			ft_is_ind_arg(char *arg)
{
	int				len;
	int				i;

	i = -1;
	len = ft_strlen(arg);
	DEBUG ? ft_printf("launching ft_is_ind_arg ...\n") : DEBUG;
	if (*arg == '-')
		i++;
	if (i + 1 == len)
		return (false);
	while (++i < len)
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
	return (true);
}

static int			ft_is_dir_arg(char *arg)
{
	int				len;
	int				i;

	len = ft_strlen(arg);
	i = 0;
	DEBUG ? ft_printf("launching ft_is_dir_arg ...\n") : DEBUG;
	if (*arg == DIRECT_CHAR && len > 1 && *(arg + 1) != LABEL_CHAR)
	{
		while (++i < len)
		{
			if (i == 1 && arg[i] == '-')
				true;
			else if (arg[i] < '0' || arg[i] > '9')
				return (false);
		}
		return (true);
	}
	return (false);
}

int					ft_is_valid_lab(char *arg, t_inst *inst, int fl)
{
	int				len;

	len = ft_strlen(arg);
	DEBUG ? ft_printf("launching ft_is_valid_lab ...\n") : DEBUG;
	if ((*arg == DIRECT_CHAR && len > 2 && *(arg + 1) == LABEL_CHAR
		&& fl == T_DIR) || (*arg == LABEL_CHAR && len > 1 && fl == T_IND))
	{
		while (inst)
		{
			if (fl == T_DIR && inst->label && !ft_strcmp(arg + 2, inst->label))
				return (true);
			if (fl == T_IND && inst->label && !ft_strcmp(arg + 1, inst->label))
				return (true);
			inst = inst->n;
		}
	}
	return (false);
}

int					ch_one_inst(t_inst *tmp, t_inst *inst)
{
	int				i;

	i = -1;
	DEBUG ? ft_printf("launching ch_one_inst ...\n") : DEBUG;
	while (g_op_tab[OP_TAB_INDEX(tmp->opcode)].param[++i])
	{
		if ((g_op_tab[OP_TAB_INDEX(tmp->opcode)].param[i] & T_DIR)
				&& tmp->args[ARG_INDEX(i)]
				&& (ft_is_valid_lab(tmp->args[ARG_INDEX(i)], inst, T_DIR)
				|| ft_is_dir_arg(tmp->args[ARG_INDEX(i)])))
			true;
		else if ((g_op_tab[OP_TAB_INDEX(tmp->opcode)].param[i] & T_IND)
				&& tmp->args[ARG_INDEX(i)]
				&& (ft_is_valid_lab(tmp->args[ARG_INDEX(i)], inst, T_IND)
				|| ft_is_ind_arg(tmp->args[ARG_INDEX(i)])))
			true;
		else if ((g_op_tab[OP_TAB_INDEX(tmp->opcode)].param[i] & T_REG)
				&& tmp->args[ARG_INDEX(i)]
				&& ft_is_valid_reg(tmp->args[ARG_INDEX(i)]))
			true;
		else
			return (false);
	}
	return (true);
}
