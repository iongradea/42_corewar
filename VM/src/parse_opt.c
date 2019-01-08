/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:36 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/08 21:22:05 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

int				ft_check_ps_uid(t_ps *ps, int uid)
{
	t_ps		*ps_back;

	ps_back = ps;
	while (ps_back)
	{
		if (uid == ps_back->uid)
			return (false);
		ps_back = ps_back->next;
	}
	return (true);
}

static int		ft_check_arg(char **av, int i, int ac, t_vm_mem *vm)
{
	if (!ft_strcmp(av[i], "-g") && i + 1 < ac)
	{
		vm->display = ft_atoi(av[++i]);
		if (vm->display == 0)
			return (0);
		vm->opt & GRAPHIC ? exit(ft_usage()) : (void)(vm->opt += GRAPHIC);
	}
	else if (!ft_strcmp(av[i], "-v") && i + 1 < ac)
	{
		vm->verbose = ft_atoi(av[++i]);
		if (ft_str_not_nb(av[i]) || vm->verbose > 5 || vm->verbose < 1)
			exit(error_msg("Invalid verbosity level."));
		g_verbose = ft_atoi(av[i]);
		if (vm->verbose == 0)
			return (0);
		vm->opt & VERBOSE ? exit(ft_usage()) : (void)(vm->opt += VERBOSE);
	}
	else if (!ft_strcmp(av[i], "-N"))
	{
		vm->ncurse = 1;
		vm->opt & NCURSE ? exit(ft_usage()) : (void)(vm->opt += NCURSE);
	}
	else
		exit(error_msg("Invalid option."));
	return (i);
}

/*
** DEBUG ? ft_printf("launching ft_parse_opt ...\n") : DEBUG;
*/

int				ft_parse_opt(int ac, char **av, t_vm_mem *vm)
{
	int			i;

	i = 0;
	while (av[++i])
	{
		if (av[i][0] == '-' && ft_strcmp(av[i], "-n") && ft_str_not_nb(av[i]))
		{
			if (!ft_strcmp(av[i], "-dump") && i + 1 < ac)
			{
				vm->dump = ft_atoi(av[++i]);
				if (vm->dump == 0)
					exit(ft_usage());
				vm->opt & DUMP ? exit(ft_usage()) : (void)(vm->opt += DUMP);
			}
			if ((i = ft_check_arg(av, i, ac, vm)) == 0)
				exit(ft_usage());
		}
		else if (ft_strcmp(av[i], "-n") == 0)
			ft_n_check(av, i);
	}
	return (EXIT_SUCCESS);
}

void			ft_jmp_opt(int ac, char **av, int *i)
{
	if (*i < ac && (!ft_strcmp(av[*i], "-dump") || !ft_strcmp(av[*i], \
									"-g") || !ft_strcmp(av[*i], "-v")))
		(*i) += 2;
	else if (*i < ac && av[*i][0] == '-')
		(*i)++;
}

int				ft_usage(void)
{
	DEBUG ? ft_printf("launching ft_usage ...\n") : DEBUG;
	ft_printf("usage: ./corewar [-N] [-g nbr] [-dump nbr] [-v nbr] [[-n nbr] \
champion.cor] ...\n\
-n <nbr>	: set \"nbr\" as number for the player\n\
-v <nbr>	: Verbosity level\n\
	- 1	: show essentials\n\
	- 2	: show lives\n\
	- 3	: show cyles\n\
	- 4	: show operations\n\
	- 5	: show deaths\n\
-N 		: advanced graphical mode using ncurse library\n\
-g <nbr-cycles>	: graphic mode, displays memory on console\n\
-dump <nbr>	: dumps the memory after N cycles\n");
	return (EXIT_SUCCESS);
}
