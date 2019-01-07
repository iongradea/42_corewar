/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:04:31 by bbichero          #+#    #+#             */
/*   Updated: 2019/01/07 15:33:41 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/ft_printf.h"

int			ft_isnumber(char *number)
{
	int		i;

	i = 0;
	ft_printf("number: %s\n", number);
	if (!number)
		return (0);

	while (number[i])
	{
		ft_printf("char: %c\n", number[i]);
		if (!ft_isdigit(number[i++]))
		{
			if (i == 0 && number[i] != '-')
				return (0);
		}
	}
	return (ft_atoi(number));
}
