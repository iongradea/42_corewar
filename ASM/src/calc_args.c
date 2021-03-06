/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/27 17:02:08 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int		calc_lab_value(char *arg, t_inst *inst)
{
	int			add;
	t_inst		*tmp;
	int			st;

	add = 0;
	tmp = inst;
	DEBUG ? ft_printf("launching calc_lab_value ...\n") : DEBUG;
	st = LABEL_CHAR == *arg ? 1 : 2;
	while (tmp)
	{
		if (tmp->label && !ft_strcmp(arg + st, tmp->label))
			return (add);
		tmp = tmp->p;
		tmp && tmp->size != UNDEFINED ? add -= tmp->size : true;
	}
	add = 0;
	tmp = inst;
	while (tmp)
	{
		if (tmp->label && !ft_strcmp(arg + st, tmp->label))
			return (add);
		tmp->size != UNDEFINED ? add += tmp->size : true;
		tmp = tmp->n;
	}
	exit(error_msg("calc_lab_value error\n"));
}

static int		calc_arg_value(char *arg, t_inst *inst)
{
	DEBUG ? ft_printf("launching calc_arg_value ...\n") : DEBUG;
	DEBUG ? ft_printf("arg : %s\n", arg) : DEBUG;
	if (ft_is_reg(arg))
		return (ft_atoi(arg + 1));
	if (*arg != LABEL_CHAR && ft_is_ind(arg))
		return (ft_atoi(arg));
	if (ft_is_lab(arg))
		return (calc_lab_value(arg, inst));
	if (ft_is_dir(arg))
		return (ft_atoi(arg + 1));
	exit(error_msg("calc_arg_value error\n"));
}

static int		calc_one_ocp(char *arg)
{
	DEBUG ? ft_printf("launching calc_one_ocp ...\n") : DEBUG;
	DEBUG ? ft_printf("arg : %s\n", arg) : DEBUG;
	if (ft_is_reg(arg))
		return (OCP_REG);
	if (ft_is_ind(arg))
		return (OCP_IND);
	if (ft_is_dir(arg))
		return (OCP_DIR);
	exit(error_msg("calc_arg_value error\n"));
}

static int		calc_ocp(t_inst *inst)
{
	int			ocp;

	ocp = 0;
	DEBUG ? ft_printf("launching calc_ocp ...\n") : DEBUG;
	if (inst->args[ARG_INDEX(0)])
		ocp += (calc_one_ocp(inst->args[ARG_INDEX(0)]) << 6);
	if (inst->args[ARG_INDEX(1)])
		ocp += (calc_one_ocp(inst->args[ARG_INDEX(1)]) << 4);
	if (inst->args[ARG_INDEX(2)])
		ocp += (calc_one_ocp(inst->args[ARG_INDEX(2)]) << 2);
	return (ocp);
}

void			calc_all_arg(t_inst *inst)
{
	t_inst		*tmp;
	int			i;

	tmp = inst;
	i = -1;
	DEBUG ? ft_printf("launching calc_all_arg ...\n") : DEBUG;
	while (tmp)
	{
		if (ft_is_valid_opcode(tmp->opcode) &&
				g_op_tab[OP_TAB_INDEX(tmp->opcode)].ocp_param)
			tmp->ocp = calc_ocp(tmp);
		while (++i < NB_ARG_MAX)
		{
			if (tmp->args[ARG_INDEX(i)])
				tmp->param[i] = calc_arg_value(tmp->args[ARG_INDEX(i)], tmp);
		}
		i = -1;
		tmp = tmp->n;
	}
}
