/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 12:52:12 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/04 18:02:16 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/inc/libft.h"
#include "../../libft/inc/ft_printf.h"

// int g_optind = 1;
// int optopt;
// char *optarg;
// int topterr = 1;
//
///*
//** Display error for ft_getopt(), illegal option, require arguments, ...
//*/
//
//static void		display_error(char *exec, char *str, int c, int opterr)
//{
//	(void)opterr;
//	char errbuf[2];
//	if (topterr)
//	{
//		errbuf[0] = c;
//		errbuf[1] = '\n';
//		write(2, exec, (unsigned)ft_strlen(exec));
//		write(2, str, (unsigned)ft_strlen(str));
//		write(2, errbuf, 2);
//	}
//}
//
///*
// ** Getopt function like system getopt
// */
//
//static int		ft_getopt(int ac, char **av, char *opts, t_vm_mem *vm)
//{
//	(void)vm;
//	static int	sp = 1;
//	int			c;
//	char		*cp;
//
//	if (sp == 1)
//	{
//		if (g_optind >= ac || av[g_optind][0] != '-' \
//				|| av[g_optind][1] == '\0')
//			return (-1);
//		else if (ft_strcmp(av[g_optind], "--") == 0)
//		{
//			g_optind++;
//			return (-1);
//		}
//	}
//	optopt = av[g_optind][sp];
//	c = av[g_optind][sp];
//	if (c == ':' || (cp = ft_strchr(opts, c)) == NULL)
//	{
//		display_error(av[0], ": illegal option -- ", c, topterr);
//		if (av[g_optind][++sp] == '\0')
//		{
//			g_optind++;
//			sp = 1;
//		}
//		return ('?');
//	}
//	if (*++cp == ':')
//	{
//		if (av[g_optind][sp+1] != '\0')
//		{
//			ft_printf("yolo1");
//			optarg = ft_strdup(&av[g_optind][sp+1]);
//		}
//		else if (++g_optind >= ac)
//		{
//			display_error(av[0], ": option requires an argument -- ", c, topterr);
//			sp = 1;
//			return ('?');
//		}
//		else
//			optarg = ft_strdup(av[g_optind++]);
//		sp = 1;
//	}
//	else
//	{
//		if (av[g_optind][++sp] == '\0')
//		{
//			sp = 1;
//			g_optind++;
//		}
//		optarg = NULL;
//	}
//	return (c);
//}
//
//static void		ft_usage_args(char *err_msg)
//{
//	if (err_msg)
//		ft_putendl(err_msg);
//	ft_putendl("Usage: ./corewar [-N] [-n uid] [-g cycles] [-v nbr] [-d cycles]");
//
//	exit(1);
//}
//
//static void		ft_init_args(t_vm_mem *vm)
//{
//	vm->args = (t_args *)malloc(sizeof(t_args));
//	vm->topt = (t_opt *)malloc(sizeof(t_opt));
//	vm->args->dump = 0;
//	vm->args->number = 0;
//	vm->args->verbose = 0;
//	vm->args->ncurses = 0;
//	vm->args->graphic = 0;
//	vm->topt->opterr = 1;
//	vm->topt->optind = 1;
//	vm->topt->optopt = 0;
//	vm->topt->optarg = "";
//}
//
//void			ft_handle_opt(int ac, char **av, t_vm_mem *vm)
//{
//	char		*opts;
//	char		opt;
//
//	ft_init_args(vm);
//	opts = "hNd:n:v:g:";
//	while ((opt = ft_getopt(ac, av, opts, vm)) != -1)
//	{
//		//ft_printf("optopt: %c\n", optopt);
//		if (opt == 'h')
//			ft_usage();
//		else if (opt == 'N')
//			vm->args->ncurses = NCURSE;
//		else if (opt == 'g')
//			!(vm->args->graphic = ft_isnumber(optarg)) ? ft_usage_args(NULL) : true;
//		else if (opt == 'n')
//			!(vm->args->number = ft_isnumber(optarg)) ? ft_usage_args(NULL) : true;
//		else if (opt == 'd')
//			!(vm->args->dump = ft_isnumber(optarg)) ? ft_usage_args(NULL) : true;
//		else if (opt == 'v')
//			!(vm->args->verbose = ft_isnumber(optarg)) ? ft_usage_args(NULL) : true;
//		else
//			ft_usage_args(NULL);
//	}
////	vm->topt->optind--;
////	while (++vm->topt->optind < ac)
////		ft_usage_args(ft_strjoin("Non-option argument ", av[vm->topt->optind]));
//
//	ft_printf("ncurses: %d\nnumber: %d\ngraphic: %d\nverbose: %d\ndump: %d\n", vm->args->ncurses, vm->args->number, vm->args->graphic, vm->args->verbose, vm->args->dump);
//	//free(vm->topt->optarg);
//}

/*
** The global variables set by getopt() include:
** optarg -- A pointer to the current option argument, if there is one.
** optind -- An index of the next argv pointer to process when getopt() is called again.
** optopt -- This is the last known option.
*/

typedef struct				s_args
{
	int						dump;
	int						number;
	int						verbose;
	int						ncurses;
	int						graphic;
}							t_args;

typedef struct	s_opt
{
	int						opterr;
	int						optind;
	int						optopt;
	char					*optarg;
}				t_opt;

typedef struct	s_vm_mem
{
	t_args		*args;
	t_opt		*topt;
}				t_vm_mem;

int opterr = 1;
int optopt;
char					*optarg;

extern int					g_optind;
int							g_optind = 1;

/*
** Display error for ft_getopt(), illegal option, require arguments, ...
*/

static void		display_error(char *exec, char *str, register int c) 
{
	if (opterr)
	{
		char errbuf[2];

		errbuf[0] = c;
		errbuf[1] = '\n';
		write(2, exec, (unsigned)ft_strlen(exec));
		write(2, str, (unsigned)ft_strlen(str));
		write(2, errbuf, 2);
	}
}

static void		ft_init_args(t_vm_mem *vm)
{
	vm->args = (t_args *)malloc(sizeof(t_args));
	vm->topt = (t_opt *)malloc(sizeof(t_opt));
	vm->args->dump = 0;
	vm->args->number = 0;
	vm->args->verbose = 0;
	vm->args->ncurses = 0;
	vm->args->graphic = 0;
	vm->topt->opterr = 1;
	vm->topt->optind = 1;
	vm->topt->optopt = 0;
	vm->topt->optarg = "";
}

static void		ft_usage_args(char *err_msg)
{
	if (err_msg)
		ft_putendl(err_msg);
	ft_putendl("Usage: ./corewar [-N] [-n uid] [-g cycles] [-v nbr] [-d cycles]");

	exit(1);
}

/*
** Getopt function like system getopt
*/

static int		ft_getopt(int ac, char **av, char *opts, t_vm_mem *vm)
{
	(void)vm;
	static int sp = 1;
	int c;
	char *cp;

	if (sp == 1)
	{
		if (g_optind >= ac || av[g_optind][0] != '-' || av[g_optind][1] == '\0')
			return (-1);
		else if (ft_strcmp(av[g_optind], "--") == 0)
		{
			g_optind++;
			return (-1);
		}
	}
	optopt = av[g_optind][sp];
	c = av[g_optind][sp];
	if (c == ':' || (cp = ft_strchr(opts, c)) == NULL)
	{
		display_error(av[0], ": illegal option -- ", c);
		if (av[g_optind][++sp] == '\0')
		{
			g_optind++;
			sp = 1;
		}
		return ('?');
	}
	if (*++cp == ':')
	{
		if (av[g_optind][sp+1] != '\0')
			optarg = ft_strdup(&av[g_optind++][sp+1]);
		else if (++optind >= ac)
		{
			display_error(av[0], ": option requires an argument -- ", c);
			sp = 1;
			return ('?');
		}
		else
		{
			ft_printf("av: %s\n", av[g_optind++]);
			optarg = ft_strdup(av[g_optind++]);
		}
		sp = 1;
	}
	else
	{
		if (av[g_optind][++sp] == '\0')
		{
			sp = 1;
			g_optind++;
		}
		optarg = NULL;
	}
	return (c);
}

int		main(int ac, char **av)
{
	char		*opts;
	char		opt;
	t_vm_mem	*vm;

	vm = (t_vm_mem *)malloc(sizeof(t_vm_mem));
	opts = "hNd:n:v:g:";
	ft_init_args(vm);
	while ((opt = getopt(ac, av, opts)) != -1)
	{
		ft_printf("optart: %s, opt: %d\n", optarg, opt);
		if (opt == 'n')
			!(ft_isnumber(optarg)) ? ft_usage_args(NULL) : optarg;
		if (opt == '?')
			ft_printf("123");
	}
//	optarg = NULL;
//	opt = 1;
//	while ((opt = ft_getopt(ac, av, opts, vm)) != -1)
//	{
//		ft_printf("optart: %s\n", optarg);
//		if (opt == 'n')
//			!(ft_isnumber(optarg)) ? ft_usage_args(NULL) : optarg;
//		else
//			exit(1);
//	}
	return (0);
}
