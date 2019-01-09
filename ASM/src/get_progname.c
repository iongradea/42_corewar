/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_progname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/27 17:09:03 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

int				ft_ch_cmd_error(char *str)
{
	int i;

	DEBUG ? ft_printf("launching ft_ch_cmd_error ...\n") : DEBUG;
	i = 0;
	if (!str)
		return (false);
	while (str[i] && str[i] != '"')
	{
		if (!ft_isspace(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static void		sub_progname_lines(char *line, int *flag, t_header *head,
									char *end)
{
	int len;

	DEBUG ? ft_printf("launching sub_progname_lines ...\n") : DEBUG;
	len = ft_strlen(head->prog_name);
	if (end)
	{
		ft_strncpy(head->prog_name + len, line, end - line - 1);
		*flag -= FL_NAME_LINES;
		*flag += FL_END_NAME_LINE;
	}
	else
	{
		ft_strcpy(head->prog_name + len, line);
		*(head->prog_name + len + ft_strlen(line)) = '\n';
	}
}

static void		progname_oneln(char *st, char *end, int *flag, t_header *head)
{
	DEBUG ? ft_printf("launching progname_oneln ...\n") : DEBUG;
	if (*(end + 1) && *(end + 1) != '#')
		exit(error_msg("Error name line\n"));
	if (end == st + 1)
		true;
	else
		ft_strncpy(head->prog_name, st + 1, end - st - 1);
	*flag += FL_NAME;
	*flag += FL_END_NAME_LINE;
}

static void		progname_multiln(char *st, int *flag, t_header *head)
{
	DEBUG ? ft_printf("launching progname_multiln ...\n") : DEBUG;
	ft_strcpy(head->prog_name, st + 1);
	*(head->prog_name + ft_strlen(st) - 1) = '\n';
	*flag += FL_NAME_LINES;
	*flag += FL_NAME;
}

int				get_prog_name(char *line, int *flag, t_header *head)
{
	char *st;
	char *end;
	char *name_st;

	st = ft_strchr(line, '"');
	end = ft_strrchr(line, '"');
	name_st = ft_strstr(line, NAME_CMD_STRING);
	if (!(*flag & FL_NAME_LINES) && ((is_name_line(line) && !st)
		|| (is_name_line(line) && ft_ch_cmd_error(name_st + NAME_CMD_LEN))))
		exit(error_msg("Error .name line\n"));
	if (*flag & FL_NAME_LINES)
	{
		if ((end && *(end + 1) && *(end + 1) != '#') || st != end)
			exit(error_msg("Error last .name line\n"));
		sub_progname_lines(line, flag, head, end);
	}
	else if (is_name_line(line) && st != end)
		ft_strchr(st + 1, '"') != end ? exit(error_msg("Error .name line\n")) \
									: progname_oneln(st, end, flag, head);
	else if (is_name_line(line) && st == end)
		progname_multiln(st, flag, head);
	if (ft_strlen(head->prog_name) > PROG_NAME_LENGTH)
		exit(error_msg("Error : name too long\n"));
	return (EXIT_SUCCESS);
}
