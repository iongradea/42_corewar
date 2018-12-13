/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igradea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 23:23:53 by igradea           #+#    #+#             */
/*   Updated: 2018/12/13 13:42:09 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int			ft_iswhite(char c)
{
	return ((c == ' ') || (c == '\n') || (c == '\t'));
}

static int	number_of_words(char *str)
{
	int		n;

	n = 0;
	while (*str)
	{
		if (ft_iswhite(*str))
			str++;
		else
		{
			n += 1;
			while (!ft_iswhite(*str) && *str)
				str++;
		}
	}
	return (n);
}

char		**ft_strsplit(char *str)
{
	int		i;
	int		j;
	int		n;
	char	**output;

	i = 0;
	n = number_of_words(str);
	output = (char **)malloc(sizeof(char*) * (n + 1));
	while (i < n)
	{
		j = 0;
		while (ft_iswhite(*str))
			str++;
		while (!ft_iswhite(str[j]) && str[j])
			j++;
		output[i] = ft_strndup(str, j);
		i++;
		str += j;
	}
	output[i] = 0;
	return (output);
}
