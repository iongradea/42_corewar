/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:04:31 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/07 16:05:08 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int			ft_isnumber(char *number)
{
	int		i;

	i = 0;
	if (!number)
		return (0);

	while (number[i])
	{
		if (!ft_isdigit(number[i++]))
		{
			if (i == 0 && number[i] != '-')
				return (0);
		}
	}
	return (ft_atoi(number));
}
