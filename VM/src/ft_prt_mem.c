/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:40:36 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/18 15:35:48 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int					ft_add_c_mem(t_vm_mem *vm, char *str)
{
	int				i;

	i = -1;
	while (str[++i])
	{
		vm->mem_color[vm->mem_color_ind] = str[i];
		vm->mem_color_ind++;
		vm->mem_color_size++;
	}
	vm->mem_color[vm->mem_color_ind] = '\0';
	return (EXIT_SUCCESS);
}

static int			ft_is_pc(t_vm_mem *vm, int index)
{
	int			i;

	i = 0;
	while (i < vm->nb_players)
	{
		if (vm->ps[i].pc == index)
			return (true);
		i++;
	}
	return (false);
}

static unsigned int	ft_get_color(t_vm_mem *vm, int index)
{
	int			i;

	i = 0;
	DEBUG ? ft_printf("launching ft_get_color ...\n") : DEBUG;
	if (vm->mem_uid[index] == NO_PLAYR && ft_is_pc(vm, index))
	{
		while (vm->ps[i].pc != index)
			i++;
		vm->mem_uid[index] = vm->ps[i].uid;
		return (vm->ps[i].color);
	}
	while (i < vm->nb_players)
	{
		if (vm->mem_uid[index] == vm->ps[i].uid)
			break ;
		i++;
	}
	if (vm->ps[i].color)
		exit(ERROR_MSG("ft_get_color : uid not found in processes ... weird!"));
	return (vm->ps[i].color);
}

/*
** DEBUG ? ft_printf("launching ft_prt_mem_loop ...\n") : DEBUG;
*/

static void			ft_prt_mem_loop(t_vm_mem *vm, int i)
{
	int				color_i;

	color_i = UNDEFINED;
	if (vm->mem_uid[i] == NO_PLAYR && !ft_is_pc(vm, i))
		ft_byte(vm, vm->mem[i]);
	else if (ft_is_pc(vm, i))
	{
		color_i = ft_get_color(vm, i);
		ft_add_c_mem(vm, (char*)g_colorpc[color_i]);
		ft_byte(vm, vm->mem[i]);
		ft_add_c_mem(vm, EOC);
	}
	else
	{
		color_i = ft_get_color(vm, i);
		ft_add_c_mem(vm, (char*)g_color[color_i]);
		ft_byte(vm, vm->mem[i]);
		ft_add_c_mem(vm, EOC);
	}
	ft_add_c_mem(vm, " ");
}

void				ft_prt_mem(t_vm_mem *vm)
{
	int				i;

	i = -1;
	vm->mem_color_ind = 0;
	vm->mem_color_size = 0;
	DEBUG ? ft_printf("launching ft_prt_mem ...\n") : DEBUG;
	system("clear");
	add_top_mem(vm);
	while (++i < MEM_SIZE)
	{
		if (i != 0 && i % MEM_LINE_LENGTH == 0)
			ft_add_c_mem(vm, "||\n||");
		ft_prt_mem_loop(vm, i);
	}
	add_bot_mem(vm);
	write(1, vm->mem_color, vm->mem_color_size);
}
