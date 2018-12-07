/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_annex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romontei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea           #+#    #+#             */
/*   Updated: 2018/11/07 21:19:59 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
**  add process at the end of process listi
*/

void			ft_add_ps(t_ps *ps, t_ps *new)
{
	static int	color = 1;

	DEBUG ? ft_printf("launching ft_add_ps ...\n") : DEBUG;
	new->color = color;
	while (ps->next)
		ps = ps->next;
	new->prev = ps;
	ps->next = new;
	color++;
}

/*
** ps->pc should always be positive
** int are casted to unsigned int during C operations
*/

int				ft_next_op(t_ps *ps, int carry_mod)
{
	DEBUG > 0 ? ft_printf("launching ft_next_op ...\n") : DEBUG;
	ps->pc = MEM_CIR_POS(ps->pc + ps->op_size);
	//ft_printf("next_op ==> ps->ps_uid : %d - pc : %d - op_size : %d\n", ps->ps_uid, ps->pc, ps->op_size);
	ps->op_size = 0;
	if (carry_mod == NO_CARRY)
		return (EXIT_SUCCESS);
	else
		ps->carry = carry_mod == CARRY_TRUE ? 1 : 0;
	return (EXIT_SUCCESS);
}

int				ft_get_code_size(int fd)
{
	int			size;
	char		c;

	size = 0;
	DEBUG > 0 ? ft_printf("launching ft_get_code_size ...\n") : DEBUG;
	lseek(fd, sizeof(t_header), SEEK_SET);
	while (read(fd, &c, 1) > 0)
		size++;
	lseek(fd, 0, SEEK_SET);
	return (size);
}

int				ft_prt_winner(t_vm_mem *vm, t_ps *ps)
{
	DEBUG ? ft_printf("launching ft_prt_winner ...\n") : DEBUG;
	while (ps)
	{
		if (ps->uid == vm->last_live)
			break ;
		ps = ps->next;
	}
	if (ps)
		ft_printf("le joueur %d(%s) a gagne\n", vm->last_live, ps->playr);
	else
		exit(ERROR_MSG("aucun joueur valide erreur ou aucun gagnant\n"));
	return (EXIT_SUCCESS);
}

int 			ft_ps_uid(void)
{
	static int  ps_uid = -1;

	ps_uid++;
	return (ps_uid);
}
