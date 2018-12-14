/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/12/14 17:49:59 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int			error_msg(char *str)
{
	ft_printf("%s\n", str);
	return (EXIT_SUCCESS);
}

int			is_invalid_reg(t_vm_mem *vm, t_ps *ps, int arg_i, int arg)
{
	return (ft_is_type(vm, ps, arg_i, T_REG) && !IS_REG(arg));
}

void		ft_new_ps_sub(t_ps *ps)
{
	ps->pc = 0;
	ps->live = 0;
	ps->op_size = 0;
	ps->opcode = 0;
	ps->fl = true;
	ps->cyc_len = 0;
	ps->next = NULL;
	ps->prev = NULL;
}

int			ft_op_size_2(t_vm_mem *vm, t_ps *ps)
{
	int		op_size;
	int		nb_arg;
	int		ocp_size;

	ocp_size = g_op_tab[ps->opcode].ocp_param;
	nb_arg = g_op_tab[ps->opcode].nb_param;
	if (nb_arg == 1)
		op_size = OPCODE_SIZE + ocp_size + ft_arg_size(vm, ps, 0);
	else if (nb_arg == 2)
		op_size = OPCODE_SIZE + ocp_size + ft_arg_size(vm, ps, 0)
			+ ft_arg_size(vm, ps, 1);
	else if (nb_arg == 3)
		op_size = OPCODE_SIZE + ocp_size + ft_arg_size(vm, ps, 0)
			+ ft_arg_size(vm, ps, 1) + ft_arg_size(vm, ps, 2);
	else
		exit(error_msg("ft_get_op_size_2 : error wrong nb_arg"));
	return (op_size);
}
