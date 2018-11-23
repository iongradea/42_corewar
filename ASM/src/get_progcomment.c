/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_progcomment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 18:45:15 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void 	sub_progcom_lines(char *line, int *flag, t_header *head, char *end)
{
	int len;

	DEBUG ? ft_printf("launching sub_progcom_lines ...\n") : DEBUG;
	len = ft_strlen(head->comment);
	if (end)
	{
		ft_strncpy(head->comment + len, line, end - line + 1);
		*flag -= FL_COMMENT_LINES;
	}
	else
	{
		ft_strcpy(head->comment + len, line);
		*(head->comment + len + ft_strlen(line)) = '\n';
	}
}

static void 	progcom_oneln(char *st, char *end, int *flag, t_header *head)
{
	DEBUG ? ft_printf("launching progcom_oneln ...\n") : DEBUG;
	if (*(end + 1) && *(end + 1) != '#')
		exit(ERROR_MSG("Error comment line\n"));
	if (end == st + 1)
		true;
	else
		ft_strncpy(head->comment, st + 1, end - st + 1);
	*flag += FL_COMMENT;
}

static void 	progcom_multiln(char *st, int *flag, t_header *head)
{
	DEBUG ? ft_printf("launching progcom_multiln ...\n") : DEBUG;
	ft_strcpy(head->comment, st + 1);
	*(head->comment + ft_strlen(st) - 1) = '\n';
	*flag += FL_COMMENT_LINES;
	*flag += FL_COMMENT;
}

int 	get_prog_comment(char *line, int *flag, t_header *head)
{
	char *st;
	char *end;
	char *com_st;

	DEBUG ? ft_printf("launching get_prog_comment ...\n") : DEBUG;
	st = ft_strchr(line, '"');
	end = ft_strrchr(line, '"');
	com_st = ft_strstr(line, COMMENT_CMD_STRING);
	if (!(*flag & FL_COMMENT_LINES) && ((IS_COMMENT_LINE(line) && !st)
		|| (IS_COMMENT_LINE(line) && ft_ch_cmd_error(line + COMMENT_CMD_LEN))))
		exit(ERROR_MSG("Error .comment line\n"));
	if (*flag & FL_COMMENT_LINES)
	{
		if ((end && *(end + 1) && *(end + 1) != '#') || st != end)
			exit(ERROR_MSG("Error last .comment line\n"));
		sub_progcom_lines(line, flag, head, end);
	}
	else if (IS_COMMENT_LINE(line) && st != end && st + 1 != end)
		progcom_oneln(st, end, flag, head);
	else if (IS_COMMENT_LINE(line) && st == end)
		progcom_multiln(st, flag, head);
	if (ft_strlen(head->comment) > COMMENT_LENGTH)
		exit(ERROR_MSG("Error : comment too long\n"));
	return (EXIT_SUCCESS);
}
