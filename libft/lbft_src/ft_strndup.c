/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbichero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:40:08 by bbichero          #+#    #+#             */
/*   Updated: 2018/12/13 13:40:16 by bbichero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strndup(char const *s1, size_t n)
{
	size_t	i;
	char	*dup;

	i = 0;
	while (s1[i] != '\0' && i < n)
		i++;
	n = i;
	dup = (char*)malloc(sizeof(char) * (i + 1));
	if (dup == 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[n] = '\0';
	return (dup);
}
