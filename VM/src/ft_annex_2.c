/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/12/09 16:45:58 by igradea          ###   ########.fr       */
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
