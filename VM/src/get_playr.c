/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_playr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:22:40 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/08 17:02:54 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vm.h"

static int			ft_get_playr_id(t_vm_mem *vm, int ac, char **av, \
										int *index)
{
	static int		i = 0;
	int				res;
	int				j;

	res = -1;
	j = -1;
	DEBUG ? ft_printf("launching ft_get_playr_index ...\n") : DEBUG;
	if (!ft_strcmp(*av, "-n"))
		(*index += 2) < ac ? res = ft_atoi(*(av + 1)) : exit(ft_usage());
	else
	{
		++i;
		while (++j < MAX_PLAYERS)
			if (i == vm->set_uid[j])
				i++;
		res = i;
	}
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
	if (ps->code_size > CHAMP_MAX_SIZE)
		exit(error_msg("champions size too large"));
	ps->ps_uid = ft_ps_uid();
	if (!(ps->code = (unsigned char *)ft_memalloc(sizeof(unsigned char) \
					* ps->code_size)))
		exit(error_msg("ft_new_ps : error heap allocation"));
	ft_bzero(ps->reg, sizeof(ps->reg));
	ps->reg[1] = uid;
	ft_new_ps_sub(ps);
	ps->color = UNDEFINED;
	ps->carry = 0;
	ps->color_pc = 10;
	return (ps);
}

static void			ft_get_ps_data(t_ps **ps, int uid, char *av)
{
	static int		nb_playr = 0;
	unsigned char	buf[4];
	int				fd;

	ft_bzero(buf, 4);
	if ((fd = open(av, O_RDONLY)) >= 0)
	{
		*ps = ft_new_ps(fd, uid);
		read(fd, buf, 4);
		buf[0] != 0x00 ? exit(error_msg("Error: wrong exec magic")) : true;
		buf[1] != 0xea ? exit(error_msg("Error: wrong exec magic")) : true;
		buf[2] != 0x83 ? exit(error_msg("Error: wrong exec magic")) : true;
		buf[3] != 0xf3 ? exit(error_msg("Error: wrong exec magic")) : true;
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

static void			get_set_uid(t_vm_mem *vm, int ac, char **av)
{
	int i;
	int j;
	int res;

	i = 0;
	j = -1;
	res = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(*(av + i), "-n"))
		{
			if (i + 1 >= ac)
				exit(ft_usage());
			if (ft_str_not_nb(*(av + i + 1)) || !ft_valid_int(*(av + i + 1)))
				exit(error_msg("Error : Invalid player uid send."));
			res = ft_atoi(*(av + i + 1));
			if (res == UNDEFINED || res == 0)
				exit(error_msg("Error : player number can't be -1 or 0"));
			if (res > 1024 || res < -1024)
				exit(error_msg("Error : uid player must be : -1024 < uid < \
																1024"));
			j > MAX_PLAYERS ? exit(ft_usage()) : true;
			vm->set_uid[++j] = res;
		}
	}
}

int					get_playr(t_vm_mem *vm, t_ps **ps, int ac, char **av)
{
	int				i;
	t_ps			*new;
	int				uid;

	i = 1;
	new = NULL;
	get_set_uid(vm, ac, av);
	while (i < ac && av[i][0] == '-' && ft_strcmp(av[i], "-n"))
		ft_jmp_opt(ac, av, &i);
	i < ac ? uid = ft_get_playr_id(vm, ac, av + i, &i) : exit(ft_usage());
	i < ac ? ft_get_ps_data(ps, uid, *(av + i)) : exit(ft_usage());
	(*ps)->color = 0;
	vm->ps_end = *ps;
	vm->nb_live_ps = 1;
	while (++i < ac)
	{
		while (i < ac && av[i][0] == '-' && ft_strcmp(av[i], "-n"))
			ft_jmp_opt(ac, av, &i);
		i < ac ? uid = ft_get_playr_id(vm, ac, av + i, &i) : exit(ft_usage());
		i < ac ? ft_get_ps_data(&new, uid, *(av + i)) : exit(ft_usage());
		if (!ft_check_ps_uid(*ps, uid))
			exit(ft_printf("UID %d already exist for another process\n", uid));
		ft_add_ps(vm, new);
	}
	return (EXIT_SUCCESS);
}
