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

int				ft_is_special_line(char *line)
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
		if (!ft_isspace(line[i]) && line[i] != SPECIAL_CHAR)
			return (false);
		if (line[i] == SPECIAL_CHAR)
			return (true);
	}
	return (false);
}






// condition : ((IS_NAME_LINE && FL_NAME_LINES == false && FL_COMMENT_LINES == false) || FL_NAME_LINES == true)

int 	get_prog_name_2(char *line, int *flag, t_header *head)
{
	char *st;
	char *end;
	int len;

	st = ft_strchr(line, '"');
	end = ft_strrchr(line, '"');
	if (FL_NAME_LINES == false && ((IS_NAME_LINE && !st) || (IS_NAME_LINE && any weird characters before '"')))
		exit(ERROR_MSG("Error .name line\n"));
	if (FL_NAME_LINES)
	{
		if ((end && !*(end + 1) && *(end + 1) != '#') || st != end)
			exit(ERROR_MSG("Error last .name line\n"));
		len = ft_strlen(head->prog_name);
		len > PROG_NAME_LENGTH ? exit(ERROR_MSG("Err: name too long\n")) : true;
		if (end)
		{
			ft_strncpy(head->prog_name + len - 1, line, line - end - 1);
			FL_NAME_LINES = false;
		}
		else
			ft_strcpy(head->prog_name + len - 1, line);
	}
	else if (IS_NAME_LINE && st != end)
	{
		if (!*(end + 1) && *(end + 1) != '#')
			exit(ERROR_MSG("Error name line\n"));
		if (end == st + 1)
			true;
		else
			ft_strncpy(head->prog_name, st + 1, st - end - 1);
		FL_NAME = true;
	}
	else if (IS_NAME_LINE && st == end)
	{
		ft_strncpy(head->prog_name, line, st + 1);
		FL_NAME_LINES = true;
		FL_NAME = true;
	}
	else
		exit(ERROR_MSG("Error unexpected\n"));
	return (EXIT_SUCCESS);
}
