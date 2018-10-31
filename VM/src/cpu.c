/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:09:29 by bbichero          #+#    #+#             */
/*   Updated: 2018/10/31 19:55:47 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/vm.h"

static int  ft_cycle_len(int opcode)
{
	int i;

	i = -1;
	while (++i < NB_OP)
	{
		if (opcode == op_tab[i].opcode)
			return (op_tab[i].cycle);
	}
	return (1);
}

int   cpu(t_vm_mem *vm, t_ps *ps)
{
	t_ps	*lst;
	int		flag;
	int		opcode;
	int		cyc_len;

	flag = false;
	lst = NULL;
	opcode = 0;
	cyc_len = 0;
	DEBUG ? ft_printf("launching cpu ...\n") : DEBUG;
	//prt_ps(ps the flag is used here to identify if the program has already passed
	// the first cycle_to_die cycle  
	while (flag == false && vm->cycle_to_die > 0 && cyc_len >= 0)
	{
		ft_printf("cyc_len = %d\nopcode = %d\nflag = %d\n", cyc_len, opcode, flag);
		if (cyc_len == 0)
		{
			opcode = *(vm->mem + MEM_CIR_POS(ps->pc));
			cyc_len = ft_cycle_len(opcode);
			if (!ft_one_live_ps(ps) || cyc_len == 1)
				break ;
			exec_op(vm, ps, lst, opcode, &flag);
		}
		cyc_len--;
		vm->cycle++;
	}
	prt_ps(ps);
	//prt_vm(vm);
	return (ft_prt_winner(vm, ps));
}
