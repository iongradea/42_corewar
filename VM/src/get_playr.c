/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_playr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:40 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/13 13:13:16 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int			ft_get_playr_index(int ac, char **av, int *index)
{
	static int		i = MAX_NB_PLAYR;
	int				res;

	res = -1;
	DEBUG ? ft_printf("launching ft_get_playr_index ...\n") : DEBUG;
	if (!ft_strcmp(*av, "-n"))
		(*index += 2) < ac ? res = ft_atoi(*(av + 1)) : exit(ft_usage());
	else
		res = --i;
	if (res == UNDEFINED || res == 0)
		exit(error_msg("Error : player number can't be -1\n"));
	return (res);
}

/*
** DEBUG ? ft_printf("launching ft_new_ps ...\n") : DEBUG;
*/

static t_ps			*ft_new_ps(int fd, int uid)
{
	t_ps			*ps;

	if (!(ps = (t_ps*)ft_memalloc(sizeof(t_ps))))
		exit(error_msg("ft_new_ps : error heap allocation"));
	if (!(ps->playr = (char*)ft_memalloc(sizeof(char) \
					* (PROG_NAME_LENGTH + 1))))
		exit(error_msg("ft_new_ps : error heap allocation"));
	ps->uid = uid;
	ps->code_size = ft_get_code_size(fd);
	ps->ps_uid = ft_ps_uid();
	if (!(ps->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) \
					* ps->code_size)))
		exit(error_msg("ft_new_ps : error heap allocation"));
	ft_bzero(ps->reg, sizeof(ps->reg));
	ps->reg[1] = uid;
	ft_new_ps_sub(ps);
	ps->color = UNDEFINED;
	ps->carry = 0;
	return (ps);
}

static void			ft_get_ps_data(int fd, t_ps **ps, int uid, char *av)
{
	static int		nb_playr = 0;
	unsigned char	buf[4];

	DEBUG ? ft_printf("launching ft_get_ps_data ...\n") : DEBUG;
	ft_bzero(buf, 4);
	if ((fd = open(av, O_RDONLY)) >= 0)
	{
		*ps = ft_new_ps(fd, uid);
		read(fd, buf, 4);
		buf[0] != 0x00 ? exit(error_msg("Error: wrong exec magic\n")) : true;
		buf[1] != 0xea ? exit(error_msg("Error: wrong exec magic\n")) : true;
		buf[2] != 0x83 ? exit(error_msg("Error: wrong exec magic\n")) : true;
		buf[3] != 0xf3 ? exit(error_msg("Error: wrong exec magic\n")) : true;
		lseek(fd, 4, SEEK_SET);
		read(fd, (*ps)->playr, PROG_NAME_LENGTH);
		lseek(fd, sizeof(t_header), SEEK_SET);
		!((*ps)->code_size) ? exit(error_msg("Error: no playr code")) : true;
		read(fd, (*ps)->code, (*ps)->code_size);
		close(fd);
		nb_playr++;
	}
	else
		exit(error_msg(ft_strjoin("Can't read given file : ", av)));
	if (nb_playr > MAX_PLAYERS)
		exit(error_msg("too many players"));
}

/*
** DEBUG ? ft_printf("launching ft_cpy_playr ...\n") : DEBUG;
*/

t_ps				*ft_cpy_playr(t_ps *ps)
{
	t_ps			*new;

	if (!(new = (t_ps*)ft_memalloc(sizeof(t_ps))))
		exit(error_msg("ft_cpy_playr : error heap allocation"));
	if (!(new->playr = (char *)ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH \
						+ 1))))
		exit(error_msg("ft_cpy_playr : error heap allocation"));
	ft_memcpy(new->playr, ps->playr, PROG_NAME_LENGTH + 1);
	new->uid = ps->uid;
	new->ps_uid = ft_ps_uid();
	new->code_size = ps->code_size;
	if (!(new->code = (unsigned char*)ft_memalloc(sizeof(char) \
					* new->code_size)))
		exit(error_msg("ft_cpy_playr : error heap allocation"));
	ft_memcpy(new->code, ps->code, new->code_size);
	ft_bzero(new->reg, sizeof(new->reg));
	ft_memcpy(new->reg, ps->reg, sizeof(new->reg));
	ft_new_ps_sub(new);
	new->color = ps->color;
	new->carry = ps->carry;
	ft_add_ps(ps, new);
	return (new);
}

int					get_playr(int fd, t_ps **ps, int ac, char **av)
{
	int				i;
	t_ps			*new;
	int				uid;

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
			exit(error_msg(ft_strjoin("UID ", ft_strjoin(ft_itoa(uid), \
								" already exist for another process."))));
		ft_add_ps(*ps, new);
	}
	return (EXIT_SUCCESS);
}
