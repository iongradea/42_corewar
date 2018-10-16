/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2013/11/06 14:21:46 by igradea              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/vm.h"

void	add_top_mem(t_vm_mem *vm)
{
	ft_add_c_mem(vm, "===============================");
	ft_add_c_mem(vm, "===============================");
	ft_add_c_mem(vm, "===============================");
	ft_add_c_mem(vm, "===============================");
	ft_add_c_mem(vm, "===============================");
	ft_add_c_mem(vm, "=========");
	ft_add_c_mem(vm, "===============================\n");
	ft_add_c_mem(vm, "||");
}

void		add_bot_mem(t_vm_mem *vm)
{
	ft_add_c_mem(vm, "\033[0m");
	ft_add_c_mem(vm, "||");
	ft_add_c_mem(vm, "\n===============================");
	ft_add_c_mem(vm, "==============================");
	ft_add_c_mem(vm, "==============================");
	ft_add_c_mem(vm, "==============================");
	ft_add_c_mem(vm, "==============================");
	ft_add_c_mem(vm, "============================================\n");
	ft_add_c_mem(vm, "\n");
}

void		ft_hex(t_vm_mem *vm, unsigned char c)
{
  char tmp[2];

  ft_bzero(tmp, 2);
	if (c >= 16)
		ft_hex(vm, c / 16);
	if ((c % 16) < 10)
  {
    tmp[0] = (c % 16) + '0';
    ft_add_c_mem(vm, tmp);
  }
	else
  {
    tmp[0] = (c % 16) - 10 + 'a';
    ft_add_c_mem(vm, tmp);
  }
}

void		ft_byte(t_vm_mem *vm, unsigned char c)
{
	if (c == 0)
    ft_add_c_mem(vm, "00");
	else if (c < 16)
	{
    ft_add_c_mem(vm, "0");
    ft_hex(vm, c);
	}
	else
  {
    ft_hex(vm, c >> 4);
    ft_hex(vm, c & 0x0f);
  }
}
