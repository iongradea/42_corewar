/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 12:52:12 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/03 16:21:49 by romontei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

/*
 * ** The global variables set by getopt() include:
 * ** optarg -- A pointer to the current option argument, if there is one.
 * ** optind -- An index of the next argv pointer to process when getopt() is called again.
 * ** optopt -- This is the last known option.
 * */
int opterr = 1;
int optind = 1;
int optopt;
char *optarg;

/*
 * ** Display error for ft_getopt(), illegal option, require arguments, ...
 * */
void		display_error(char *exec, char *str, register int c) 
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

/*
 * ** Getopt function like system getopt
 * */
int		ft_getopt(int ac, char **av, char *opts)
{
	static int sp = 1;
	register int c;
	register char *cp;

	if (sp == 1)
	{
		if (optind >= ac || av[optind][0] != '-' || av[optind][1] == '\0')
			return (-1);
		else if (ft_strcmp(av[optind], "--") == 0)
		{
			optind++;
			return (-1);
		}
	}
	optopt = av[optind][sp];
	c = av[optind][sp];
	if (c == ':' || (cp = ft_strchr(opts, c)) == NULL)
	{
		display_error(av[0], ": illegal option -- ", c);
		if (av[optind][++sp] == '\0')
		{
			optind++;
			sp = 1;
		}
		return ('?');
	}
	if (*++cp == ':')
	{
		if (av[optind][sp+1] != '\0')
			optarg = &av[optind++][sp+1];
		else if (++optind >= ac)
		{
			display_error(av[0], ": option requires an argument -- ", c);
			sp = 1;
			return ('?');
		}
		else
			optarg = av[optind++];
		sp = 1;
	}
	else
	{
		if (av[optind][++sp] == '\0')
		{
			sp = 1;
			optind++;
		}
		optarg = NULL;
	}
	return (c);
}


int			main(int ac, char **av)
{
	char	*opts;
	char	opt;
	int		i = 0;

	opts = "Nd:n:v:g: --ncurses,--dump:,--number:,--verbose,--graphic";
	while ((opt = ft_getopt(ac, av, opts)) != -1)
	{
		if (opt == 'N')
		{
			ft_printf("NCURSE\n");
		}
		else if (opt == 'n')
		{
			!ft_isdigit(optarg) ? exit(ft_usage()) : true;
		}
		else
		{
			ft_printf("Usage: %s [-t nsecs] [-n] name\n", av[0]);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

