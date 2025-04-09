/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:23:16 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/19 11:25:46 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	size_check(char const *s1, char const *set)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = ft_strlen(s1) - 1;
	while (is_charset(s1[i], set) && s1[i])
		i++;
	if (!(is_charset(s1[i], set) && s1[i]))
		i--;
	while (is_charset(s1[j], set) && j >= 0)
		j--;
	return (j - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	j;
	size_t	i;
	char	*res;
	int		size;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	size = size_check(s1, set);
	if (size <= 0)
		return (ft_strdup(""));
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	while (is_charset(s1[i], set) && s1[1])
		i++;
	res[size] = '\0';
	while (j < (size_t)size)
		res[j++] = s1[i++];
	return (res);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int	main(int ac, char **av)
{
	(void)ac;
	char *str = ft_strtrim(av[1], av[2]);
	printf("%s\n", str);
	free(str);
	return (0);
}*/
