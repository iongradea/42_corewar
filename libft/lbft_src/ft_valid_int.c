/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 15:10:40 by igradea           #+#    #+#             */
/*   Updated: 2018/12/15 17:32:25 by igradea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void		ft_start(const char *str, int *i, int *sign)
{
	while (ft_isspace(str[*i]) == 1)
		(*i)++;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
		(*i)++;
}

int				ft_valid_int(const char *str)
{
	int	nb;
	int prev;
	int	sign;
	int	i;

	i = 0;
	nb = 0;
	sign = 1;
	prev = nb;
	ft_start(str, &i, &sign);
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		prev = nb;
		nb = nb * 10 + str[i] - '0';
		i++;
		if ((nb < prev && nb != -2147483648) \
		|| (nb == -2147483648 && str[i] >= '0' && str[i] <= '9') \
		|| (nb == -2147483648 && sign == 1))
			return (0);
	}
	return (1);
}
