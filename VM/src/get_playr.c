/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_playr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:40 by bbichero          #+#    #+#             */
/*   Updated: 2018/11/05 21:27:12 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int		ft_get_playr_index(int ac, char **av, int *index)
{
	static int	i = MAX_NB_PLAYR;
	int			res;

	res = -1;
	DEBUG ? ft_printf("launching ft_get_playr_index ...\n") : DEBUG;
	if (!ft_strcmp(*av, "-n"))
		(*index += 2) < ac ? res = ft_atoi(*(av + 1)) : exit(ft_usage());
	else
		res = --i;
	return (res);
}

static t_ps		*ft_new_ps(int fd, int uid)
{
	t_ps		*ps;

	DEBUG ? ft_printf("launching ft_new_ps ...\n") : DEBUG;
	if (!(ps = (t_ps*)ft_memalloc(sizeof(t_ps))))
		exit(ERROR_MSG("ft_new_ps : error heap allocation"));
	if (!(ps->playr = (char*)ft_memalloc(sizeof(char) \
									* (PROG_NAME_LENGTH + 1))))
		exit(ERROR_MSG("ft_new_ps : error heap allocation"));
	ps->uid = uid;
	ps->code_size = ft_get_code_size(fd);
	if (!(ps->code \
			 = (unsigned char *)ft_memalloc(sizeof(unsigned char) * ps->code_size)))
		exit(ERROR_MSG("ft_new_ps : error heap allocation"));
	ft_bzero(ps->reg, sizeof(ps->reg));
	ps->reg[0] = uid;
	ps->pc = 0;
	ps->carry = 0;
	ps->next = NULL;
	ps->op_size = 0;
	ps->live = 0;
	ps->cyc_len = 0;
	ps->opcode = 0;
	ps->color = UNDEFINED;
	return (ps);
}

static void		ft_get_ps_data(int fd, t_ps **ps, int uid, char *av)
{
	static int	nb_playr = 0;

	DEBUG ? ft_printf("launching ft_get_ps_data ...\n") : DEBUG;
	if ((fd = open(av, O_RDONLY)) >= 0)
	{
		*ps = ft_new_ps(fd, uid);
		lseek(fd, 4, SEEK_SET);
		read(fd, (*ps)->playr, PROG_NAME_LENGTH);
		lseek(fd, sizeof(header_t), SEEK_SET);
		read(fd, (*ps)->code, (*ps)->code_size);
		close(fd);
		nb_playr++;
	}
	else
		exit(ERROR_MSG(ft_strjoin("Can't read given file : ", av)));
	if (nb_playr > 4)
		exit(ERROR_MSG("too many players"));
}

t_ps			*ft_cpy_playr(t_ps *ps)
{
	t_ps		*new;

	DEBUG ? ft_printf("launching ft_new_ps ...\n") : DEBUG;
	if (!(new = (t_ps*)ft_memalloc(sizeof(t_ps))))
		exit(ERROR_MSG("ft_cpy_playr : error heap allocation"));
	if (!(new->playr = (char *)ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH \
																	+ 1))))
		exit(ERROR_MSG("ft_cpy_playr : error heap allocation"));
	ft_memcpy(new->playr, ps->playr, PROG_NAME_LENGTH + 1);
	new->uid = ps->uid;
	new->code_size = ps->code_size;
	if (!(new->code = (unsigned char*)ft_memalloc(sizeof(char) \
														* new->code_size)))
		exit(ERROR_MSG("ft_cpy_playr : error heap allocation"));
	ft_memcpy(new->code, ps->code, new->code_size);
	ft_bzero(new->reg, sizeof(new->reg));
	ft_memcpy(new->reg, ps->reg, sizeof(new->reg));
	new->reg[0] = ps->uid;
	new->pc = 0;
	new->carry = ps->carry;
	ft_add_ps(ps, new);
	new->op_size = 0;
	new->live = 0;
	new->color = ps->color;
	return (new);
}

int				get_playr(int fd, t_ps **ps, int ac, char **av)
{
	int			i;
	t_ps		*new;
	int			uid;

	i = 1;
	new = NULL;
	DEBUG ? ft_printf("launching get_playr ...\n") : DEBUG;
	g_verbose == 1 ? ft_printf("Introducing players ...\n") : g_verbose;
	while (i < ac && av[i][0] == '-' && ft_strcmp(av[i], "-n"))
		ft_jmp_opt(ac, av, &i);
	i < ac ? uid = ft_get_playr_index(ac, av + i, &i) : exit(ft_usage());
	i < ac ? ft_get_ps_data(fd, ps, uid, *(av + i)) : exit(ft_usage());
	(*ps)->color = 0;
	while (++i < ac)
	{
		while (i < ac && av[i][0] == '-' && ft_strcmp(av[i], "-n"))
			ft_jmp_opt(ac, av, &i);
		i < ac ? uid = ft_get_playr_index(ac, av + i, &i) : exit(ft_usage());
		i < ac ? ft_get_ps_data(fd, &new, uid, *(av + i)) : exit(ft_usage());
		if (!ft_check_ps_uid(*ps, uid))
			exit(ERROR_MSG(ft_strjoin("UID ", ft_strjoin(ft_itoa(uid), \
									" already exist for another process."))));
		ft_add_ps(*ps, new);
	}
//	prt_ps(*ps);
	return (EXIT_SUCCESS);
}
