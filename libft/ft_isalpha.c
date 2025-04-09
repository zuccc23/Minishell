/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:54:45 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/10/25 19:54:45 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
/*
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int	main(int ac, char **av)
{
	(void)ac;
	printf("%d\n",ft_isalpha(atoi(av[1])));
	printf("%d\n",isalpha(atoi(av[1])));
	printf("%d\n",ft_isalpha(97));
	printf("%d\n",isalpha(97));
	return (0);
}*/