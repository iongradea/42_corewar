/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/27 17:05:24 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int				ft_is_valid_opcode(int opcode)
{
	DEBUG ? ft_printf("launching ft_is_valid_opcode ...\n") : DEBUG;
	if (opcode >= LIVE && opcode <= AFF)
		return (true);
	return (false);
}

int				ft_is_empty_line(char *line)
{
	int			len;
	int			i;

	i = -1;
	DEBUG ? ft_printf("launching ft_is_empty_line ...\n") : DEBUG;
	len = ft_strlen(line);
	while (++i < len)
	{
		if (!ft_isspace(line[i]) && line[i] != COMMENT_CHAR)
			return (false);
		if (line[i] == COMMENT_CHAR)
			return (true);
	}
	return (true);
}

int				IS_COMMENT_LINE(char *line)
{
	int		i;
	int		len;
	int		len_cmd;

	i = -1;
	len = ft_strlen(line);
	len_cmd = ft_strlen(COMMENT_CMD_STRING);
	while (++i < len)
	{
		if (!ft_isspace(line[i]) &&
			ft_strncmp(line + i, COMMENT_CMD_STRING, len_cmd))
			return (false);
		if (!ft_strncmp(line + i, COMMENT_CMD_STRING, len_cmd))
			return (true);
	}
	return (false);
}

int				IS_NAME_LINE(char *line)
{
	int		i;
	int		len;
	int		len_cmd;

	i = -1;
	len = ft_strlen(line);
	len_cmd = ft_strlen(NAME_CMD_STRING);
	while (++i < len)
	{
		if (!ft_isspace(line[i]) &&
			ft_strncmp(line + i, NAME_CMD_STRING, len_cmd))
			return (false);
		if (!ft_strncmp(line + i, NAME_CMD_STRING, len_cmd))
			return (true);
	}
	return (false);
}

char			*s_to_cor(char *str)
{
	int			i;
	char		*new;

	DEBUG ? ft_printf("launching s_to_cor ...\n") : DEBUG;
	if ((new = (char*)malloc(sizeof(char) * ft_strlen(str) + 3)) == NULL)
		exit(0);
	i = 0;
	while ((ft_strcmp(&str[i], ".s")) != 0)
	{
		if (i == (int)ft_strlen(str) - 1)
			exit(ERROR_MSG("Usage: ./asm <sourcefile.s>\n"));
		new[i] = str[i];
		i++;
	}
	new[i] = '.';
	new[i + 1] = 'c';
	new[i + 2] = 'o';
	new[i + 3] = 'r';
	new[i + 4] = '\0';
	return (new);
}
