/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iongradea <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by iongradea         #+#    #+#             */
/*   Updated: 2018/11/27 17:06:31 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void			prt_arg(int fd, int arg, int len)
{
	int				i;
	unsigned char	ch;

	i = -1;
	ch = 0;
	DEBUG ? ft_printf("launching prt_arg ...\n") : DEBUG;
	DEBUG ? ft_printf("arg : %#032x - len : %d\n", arg, len) : DEBUG;
	while (++i < len)
	{
		ch = (unsigned char)(arg >> ((len - i - 1) * 8));
		ft_putchar_fd(ch, fd);
		DEBUG ? ft_printf("ch : %#02x\n", ch) : DEBUG;
	}
}

static void			out_one_inst(int fd, t_inst *inst)
{
	int				i;
	int				size;

	i = -1;
	size = 0;
	DEBUG ? ft_printf("launching out_one_inst ...\n") : DEBUG;
	if (ft_is_valid_opcode(inst->opcode))
	{
		ft_putchar_fd((unsigned char)inst->opcode, fd);
		if (g_op_tab[OP_TAB_INDEX(inst->opcode)].ocp_param)
			ft_putchar_fd((unsigned char)inst->ocp, fd);
		while (++i < NB_ARG_MAX)
		{
			if (inst->args[ARG_INDEX(i)])
			{
				prt_arg(fd, inst->param[i], \
						ft_arg_size(inst->args[ARG_INDEX(i)], inst->opcode));
			}
		}
	}
}

void				out_all_inst(int fd, t_inst *inst)
{
	t_inst			*tmp;

	tmp = inst;
	DEBUG ? ft_printf("launching out_all_inst ...\n") : DEBUG;
	DEBUG ? prt_inst(inst) : DEBUG;
	while (tmp)
	{
		out_one_inst(fd, tmp);
		tmp = tmp->n;
	}
}

static void			head_add_bit_struct_padding(int fd)
{
	ft_putchar_fd((unsigned char)('\0'), fd);
	ft_putchar_fd((unsigned char)('\0'), fd);
	ft_putchar_fd((unsigned char)('\0'), fd);
}

void				out_header(int fd, t_header *head, int size)
{
	int				i;

	i = -1;
	DEBUG ? ft_printf("launching out_header ...\n") : DEBUG;
	ft_putchar_fd((unsigned char)(head->magic >> 24), fd);
	ft_putchar_fd((unsigned char)(head->magic >> 16), fd);
	ft_putchar_fd((unsigned char)(head->magic >> 8), fd);
	ft_putchar_fd((unsigned char)(head->magic), fd);
	DEBUG ? ft_printf("magic : %#010x\nname : %s\ncomment : %s\n",\
			head->magic, head->prog_name, head->comment) : DEBUG;
	while (++i < PROG_NAME_LENGTH + 1)
		ft_putchar_fd((unsigned char)*(head->prog_name + i), fd);
	head_add_bit_struct_padding(fd);
	ft_putchar_fd((unsigned char)(size >> 24), fd);
	ft_putchar_fd((unsigned char)(size >> 16), fd);
	ft_putchar_fd((unsigned char)(size >> 8), fd);
	ft_putchar_fd((unsigned char)(size), fd);
	i = -1;
	while (++i < COMMENT_LENGTH + 1)
		ft_putchar_fd((unsigned char)*(head->comment + i), fd);
	head_add_bit_struct_padding(fd);
}
