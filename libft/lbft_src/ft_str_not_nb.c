/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_not_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 15:10:40 by igradea           #+#    #+#             */
/*   Updated: 2018/12/15 17:32:25 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void		ft_start(const char *str, int *i)
{
	while (ft_isspace(str[*i]) == 1)
		(*i)++;
	if (str[*i] == '-')
		(*i)++;
	else if (str[*i] == '+')
		(*i)++;
}

int				ft_str_not_nb(const char *str)
{
	int	i;

	i = 0;
	ft_start(str, &i);
	while (str[i])
	{
		if (str[i] != '\0' && !ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
