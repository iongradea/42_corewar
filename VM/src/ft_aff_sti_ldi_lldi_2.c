/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_sti_ldi_lldi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:47:52 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/08 15:41:07 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int					ft_sti_2(t_vm_mem *vm, t_ps *ps, int arg1, int arg2)
{
	int				sum;

	sum = 0;
	if (ft_is_type(vm, ps, 1, T_REG))
		sum = ps->reg[arg1];
	else if (ft_is_type(vm, ps, 1, T_IND))
		sum = ft_get_ind(ps, vm, arg1, false);
	else
		sum = arg1;
	sum += ft_is_type(vm, ps, 2, T_REG) ? ps->reg[arg2] : arg2;
	return (sum);
}

int					ft_ldi_2(t_vm_mem *vm, t_ps *ps, int arg0, int arg1)
{
	int				sum;

	sum = 0;
	if (ft_is_type(vm, ps, 0, T_REG))
		sum = ps->reg[arg0];
	else if (ft_is_type(vm, ps, 0, T_IND))
		sum = ft_get_ind(ps, vm, arg0, false);
	else
		sum = arg0;
	sum += ft_is_type(vm, ps, 1, T_REG) ? ps->reg[arg1] : arg1;
	return (sum);
}

int					ft_lldi_2(t_vm_mem *vm, t_ps *ps, int arg0, int arg1)
{
	int				sum;

	sum = 0;
	if (ft_is_type(vm, ps, 0, T_REG))
		sum = ps->reg[arg0];
	else if (ft_is_type(vm, ps, 0, T_IND))
		sum = ft_get_ind(ps, vm, arg0, true);
	else
		sum = arg0;
	sum += ft_is_type(vm, ps, 1, T_REG) ? ps->reg[arg1] : arg1;
	return (sum);
}
