/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 18:45:15 by bbichero         ###   ########.fr       */
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
	if (line == NULL)
		return (true);
	else
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

int				get_prog_comment(char *line, int *flag, t_header *head)
{
	int			comment_cmd_len;

	DEBUG ? ft_printf("launching get_prog_comment ...\n") : DEBUG;
	//DEBUG ? ft_printf("LINE : %s\n", line) : DEBUG;
	comment_cmd_len = ft_strlen(COMMENT_CMD_STRING);
	if (*flag & FL_COMMENT)
		exit(ERROR_MSG("parsing error: 2 comment lines\n"));
	if (ft_strnstr(line, COMMENT_CMD_STRING, comment_cmd_len))
	{
		ft_strcpy(head->comment, line + comment_cmd_len);
		*flag += FL_COMMENT;
	}
	else
		ft_strcpy(head->comment + ft_strlen(head->comment), line);
	return (EXIT_SUCCESS);
}
