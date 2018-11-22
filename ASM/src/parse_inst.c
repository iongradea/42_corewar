/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 19:33:21 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static t_inst		*ft_new_inst(char *line)
{
	t_inst			*inst;
	int				i;

	i = -1;
	DEBUG ? ft_printf("launching ft_new_inst ...\n") : DEBUG;
	DEBUG ? ft_printf("new inst - line : %s\n", line) : DEBUG;
	if (!(inst = ft_memalloc(sizeof(t_inst))))
		exit(ERROR_MSG("malloc error\n"));
	if (!(inst->line = ft_memalloc(strlen(line) + 1)))
		exit(ERROR_MSG("mallor error\n"));
	inst->opcode = UNDEFINED;
	while (inst->args[++i])
		inst->args[i] = NULL;
	inst->label = NULL;
	inst->n = NULL;
	inst->p = NULL;
	inst->ocp = UNDEFINED;
	i = -1;
	while (++i < NB_ARG_MAX)
		inst->param[i] = UNDEFINED;
	inst->size = UNDEFINED;
	return (inst);
}

static void			ft_clean_comment(char **str)
{
	int				i;
	int				len;

	DEBUG ? ft_printf("launching ft_clean_comment ...\n") : DEBUG;
	i = -1;
	len = ft_strlen(*str);
	while (++i < len)
	{
		if ((*str)[i] == COMMENT_CHAR)
			while (i < len)
				(*str)[i++] = ' ';
	}
}

static void			ft_clean_sp(char **str)
{
	int				i;
	int				len;

	i = -1;
	DEBUG ? ft_printf("launching ft_clean_sp ...\n") : DEBUG;
	len = ft_strlen(*str);
	while (++i < len)
	{
		if ((*str)[i] == SEPARATOR_CHAR)
			(*str)[i] = ' ';
	}
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
	DEBUG ? ft_printf("launching get_inst_sub ...\n") : DEBUG;
	ft_clean_comment(&line);
	ft_clean_sp(&line);
	ft_strcpy(inst->line, line);
	tab = ft_strsplit(line);
	//DEBUG ? ft_printf("HEREE\n") : DEBUG;
	if (!ft_arrlen(tab))
		return (EXIT_SUCCESS);
	ft_ch_err_lab(tab[0]) ? exit(ERROR_MSG("syntax error\n")) : true;
	if (ft_ch_rm_lab_c(&tab[0]) && (index = 1))
		inst->label = ft_strdup(ft_strtrim(tab[0]));
	if (ft_arrlen(tab) > 1)
	{
		ft_arrlen(tab) < 2 ? exit(ERROR_MSG("syntax error\n")) : true;
		!ft_ch_opcode(tab[index]) ? exit(ERROR_MSG("syntax error\n")) : true;
		inst->opcode = op_tab[ft_ret_opcode(tab[index])].opcode;
		while (((++i + index) < ft_arrlen(tab)) && tab[i + index])
			inst->args[i] = ft_strdup(ft_strtrim(tab[i + index]));
	}
	ft_free_tab(tab);
	return (EXIT_SUCCESS);
}

/*
** DEBUG ? ft_printf("launching get_inst ...\n") : DEBUG;
** DEBUG ? ft_printf("LINE : %s\n", line) : DEBUG;
*/

int					get_inst(char *line, t_inst **inst, t_header *head)
{
	t_inst			*new;
	t_inst			*tmp;
	static int		flag = FL_STANDARD;

	tmp = *inst;
	DEBUG ? ft_printf("launching get_inst ...\n") : DEBUG;
	//DEBUG ? ft_printf("LINE : %s\n", line) : DEBUG;
	if (IS_COMMENT_LINE)
		return (get_prog_comment(line, &flag, head));
	else if ((IS_NAME_LINE && !(flag & FL_NAME)) || FL_NAME_LINES & flag)
		return (get_prog_name(line, &flag, head));
	else if (ft_is_empty_line(line))
		return (EXIT_SUCCESS);
	else if (ft_is_special_line(line))
		exit(ERROR_MSG("Lexical error\n"));
	if (tmp && tmp->n)
		while (tmp->n)
			tmp = tmp->n;
	new = ft_new_inst(line);
	if (!tmp)
		*inst = new;
	else
	{
		tmp->n = new;
		new->p = tmp;
	}
	return (get_inst_sub(line, new));
}
