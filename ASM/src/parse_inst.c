/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2019/01/08 17:57:14 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static int			ft_ch_sp_c(char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	i--;
	while (ft_isspace(line[i]))
		i--;
	if (line[i] == SEPARATOR_CHAR)
		exit(error_msg("Syntax error: comma at end of line\n"));
	return (true);
}

static void			init_get_inst_sub(char ***tab, char **line, t_inst *inst)
{
	DEBUG ? ft_printf("launching init_get_inst_sub ...\n") : DEBUG;
	ft_clean_comment(line);
	ft_ch_sp_c(*line);
	ft_clean_sp(line);
	ft_strcpy(inst->line, *line);
	*tab = ft_strsplit(*line);
}

/*
** DEBUG ? ft_printf("launching get_inst_sub ...\n") : DEBUG;
** DEBUG ? prt_tab(tab) : DEBUG;
*/

static int			get_inst_sub(char *line, t_inst *inst)
{
	char			**tab;
	int				index;
	int				i;

	index = 0;
	i = -1;
	init_get_inst_sub(&tab, &line, inst);
	if (!ft_arrlen(tab))
		return (EXIT_SUCCESS);
	ft_ch_err_lab(tab[0]) ? exit(error_msg("syntax error\n")) : true;
	if (ft_ch_rm_lab_c(&tab[0]) && (index = 1))
		inst->label = ft_strtrim(tab[0]);
	(index != 1 && (!ft_ch_opcode(tab[index]) || (ft_ch_opcode(tab[index]) \
	&& ft_arrlen(tab) == 1))) ? exit(error_msg("syntax error\n")) : true;
	if (ft_arrlen(tab) > 1)
	{
		!ft_ch_opcode(tab[index]) ? exit(error_msg("syntax error\n")) : true;
		inst->opcode = g_op_tab[ft_ret_opcode(tab[index])].opcode;
		if (ft_arrlen(tab) - index !=
			OPCODE + g_op_tab[ft_ret_opcode(tab[index])].nb_max_par)
			exit(error_msg("Error, wrong number of parameters\n"));
		while (((++i + index) < ft_arrlen(tab)) && tab[i + index])
			inst->args[i] = ft_strtrim(tab[i + index]);
	}
	return (ft_free_tab(tab));
}

static void			get_inst_annex(t_inst *new, t_inst *tmp, t_inst **inst)
{
	if (!tmp)
		*inst = new;
	else
	{
		tmp->n = new;
		new->p = tmp;
	}
}

int					get_inst(char *line, t_inst **inst, t_header *head, int *fl)
{
	t_inst			*new;
	t_inst			*tmp;

	tmp = *inst;
	DEBUG ? ft_printf("launching get_inst ...\n") : DEBUG;
	if (ft_is_empty_line(line))
		return (EXIT_SUCCESS);
	else if ((is_comment_line(line) && !(*fl & FL_COMMENT))
			|| (FL_COMMENT_LINES & *fl))
		return (get_prog_comment(line, fl, head));
	else if ((is_name_line(line) && !(*fl & FL_NAME))
			|| (FL_NAME_LINES & *fl))
		return (get_prog_name(line, fl, head));
	else if (ft_is_special_line(line))
		exit(error_msg("Lexical error\n"));
	if (tmp && tmp->n)
		while (tmp->n)
			tmp = tmp->n;
	new = ft_new_inst(line);
	get_inst_annex(new, tmp, inst);
	return (get_inst_sub(line, new));
}
