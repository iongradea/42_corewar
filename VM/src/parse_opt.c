/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:36 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/03 11:53:25 by romontei         ###   ########.fr       */
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
		vm->ncurse == 1 ? exit(ft_usage()) : (void)(vm->opt += GRAPHIC);
	}
	else if (!ft_strcmp(av[i], "-v") && i + 1 < ac)
	{
		vm->verbose = ft_atoi(av[++i]);
		g_verbose = ft_atoi(av[i]);
		if (vm->verbose == 0)
			return (0);
		vm->ncurse == 1 ? exit(ft_usage()) : (void)(vm->opt += VERBOSE);
	}
	else if (!ft_strcmp(av[i], "-N"))
	{
		vm->ncurse = 1;
		vm->opt != 0 ? exit(ft_usage()) : (void)(vm->opt += NCURSE);
	}
	else
		exit(ft_printf("Unknown option: %s\n", av[i]));
	return (i);
}

int				ft_parse_opt(int ac, char **av, t_vm_mem *vm)
{
	int			i;

	DEBUG ? ft_printf("launching ft_parse_opt ...\n") : DEBUG;
	i = 0;
	while (av[++i])
	{
		if (av[i][0] == '-' && ft_strcmp(av[i], "-n"))
		{
			if (!ft_strcmp(av[i], "-dump") && i + 1 < ac)
			{
				vm->dump = ft_atoi(av[++i]);
				if (vm->dump == 0)
					exit(ft_usage());
				vm->opt += DUMP;
				vm->ncurse == 1 ? exit(ft_usage()) : (void)(vm->opt += DUMP);
			}
			if ((i = ft_check_arg(av, i, ac, vm)) == 0)
				exit(ft_usage());
		}
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
	ft_printf("usage: ./corewar [options] [[-n nbr] champion.cor] ...\n\
-v <nbr>		: Verbosity level\n\
	- 1		: show essentials\n\
	- 2		: show lives\n\
	- 3		: show cyles\n\
	- 4		: show operations\n\
	- 5		: show deaths\n\
-N 			: advanced graphical mode using ncurse library\n\
-g <nbr-cycles>	: graphic mode, displays memory on console\n\
-dump <nbr>		: dumps the memory after N cycles\n\
-n <nbr>		: set \"nbr\" as number for the player\n");
	return (EXIT_SUCCESS);
}
