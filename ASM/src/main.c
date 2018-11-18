/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/07 19:28:41 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void		parse_input(char *str, t_inst **inst, t_header *head)
{
	int			fd;
	char		*line;

	DEBUG ? ft_printf("launching parse_input ...\n") : DEBUG;
	line = NULL;
	if ((fd = open(str, O_RDONLY)) < 1)
		exit(ERROR_MSG("error opening file\n"));
	while (get_next_line(fd, &line) > 0)
	{
		get_inst(line, inst, head);
		DEBUG ? ft_printf("gnl - line : %s\n", line) : DEBUG;
		free(line);
	}
	close(fd);
}

static void		create_file(char *av, t_inst *inst, t_header *head)
{
	int			fd;
	char		*new;

	DEBUG ? ft_printf("launching create_file ...\n") : DEBUG;
	new = s_to_cor(av);
	if ((fd = open(new, O_CREAT | O_WRONLY, 0666)) < 1)
		exit(ERROR_MSG("can't creat file .cor\n"));
	out_header(fd, head);
	out_all_inst(fd, inst);
	ft_printf("Writing output to .cor file\n");
	close(fd);
}

static void		ft_init_head(t_header *head)
{
	DEBUG ? ft_printf("launching ft_init_head ...\n") : DEBUG;
	head->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(head->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(head->comment, COMMENT_LENGTH + 1);
}

int				main(int ac, char **av)
{
	int			i;
	t_inst		*inst;
	t_header	head;

	i = 0;
	inst = NULL;
	DEBUG ? ft_printf("launching main ...\n") : DEBUG;
	while (++i < ac)
	{
		ft_init_head(&head);
		parse_input(av[i], &inst, &head);
		DEBUG ? prt_inst(inst) : DEBUG;
		ch_all_inst(inst);
		calc_all_size(inst);
		calc_all_arg(inst);
		create_file(av[i], inst, &head);
		DEBUG ? prt_inst(inst) : DEBUG;
	}
	exit(0);
}
