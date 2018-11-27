/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/27 17:03:05 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int			ft_is_special_line(char *line)
{
	int			len;
	int			i;

	i = -1;
	DEBUG ? ft_printf("launching ft_is_special_line ...\n") : DEBUG;
	len = ft_strlen(line);
	while (++i < len)
	{
		if (!ft_isspace(line[i]) && line[i] != SPECIAL_CHAR)
			return (false);
		if (line[i] == SPECIAL_CHAR)
			return (true);
	}
	return (false);
}

t_inst		*ft_new_inst(char *line)
{
	t_inst			*inst;
	int				i;

	i = -1;
	DEBUG ? ft_printf("launching ft_new_inst ...\n") : DEBUG;
	if (!(inst = ft_memalloc(sizeof(t_inst))))
		exit(error_msg("malloc error\n"));
	if (!(inst->line = ft_memalloc(strlen(line) + 1)))
		exit(error_msg("mallor error\n"));
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

void		ft_clean_comment(char **str)
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

void		ft_clean_sp(char **str)
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

int			error_msg(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return (EXIT_SUCCESS);
}
