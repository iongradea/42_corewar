/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by igradea               #+#    #+#         */
/*   Updated: 2018/10/27 15:27:11 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/vm.h"

int				ft_check_ps_uid(t_ps **ps, int uid)
{
	t_ps		*ps_back;
	
	ps_back = *ps;
	ft_printf("1231");
	while (ps_back)
	{
		ft_printf("ps_back->uid: %d\n", ps_back->uid);
		if (uid == ps_back->uid)
			return (0);
		ps_back = ps_back->next;
	}
	return (1);
}

int   ft_parse_opt(int ac, char **av, t_vm_mem *vm)
{
	int   i;

	DEBUG ? ft_printf("launching ft_parse_opt ...\n") : DEBUG;
	i = 0;
	while (av[++i])
	{
		ft_printf("av[%d] = %s\n", i, av[i]);
		if (av[i][0] == '-' && ft_strcmp(av[i], "-n"))
		{
			if (!ft_strcmp(av[i], "-dump") && i + 1 < ac)
			{
				vm->dump = ft_atoi(av[++i]);
				if (vm->dump == 0)
					exit(ft_usage());
				vm->opt += DUMP;
			}
			else if (!ft_strcmp(av[i], "-g") && i + 1 < ac)
			{
				vm->display = ft_atoi(av[++i]);
				if (vm->display == 0)
					exit(ft_usage());
				vm->opt += GRAPHIC;
			}
			else if (!ft_strcmp(av[i], "-v") && i + 1 < ac)
			{
				vm->verbose = ft_atoi(av[++i]);
				g_verbose = ft_atoi(av[i]);
				if (vm->verbose == 0)
					exit(ft_usage());
				vm->opt += VERBOSE;
			}
		}
	}
	return (EXIT_SUCCESS);
}

void ft_jmp_opt(int ac, char **av, int *i)
{
	if (*i < ac && (!ft_strcmp(av[*i], "-dump") || !ft_strcmp(av[*i], "-g")))
		(*i) += 2;
	else if (*i < ac && av[*i][0] == '-')
		(*i)++;
}

int   ft_usage(void)
{
	DEBUG ? ft_printf("launching ft_usage ...\n") : DEBUG;
	ft_printf("\nusage: ./coreware [options] [[-n nbr] champion.cor] ...\n\
			-v information_lvl : verbose mode with different type inforamtions \n\
			-g nbr_cycles      : graphic mode, displays memory on console\n\
			-dump nb_cycles    : dumps the memory after nb_cycles\n\
			-n nbr             : set \"nbr\" as number for the player\n");
	return (EXIT_SUCCESS);
}
