/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:42:31 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/20 13:30:19 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	check_size(long n)
{
	long	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = n * (-1);
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*resu;
	long	nb;
	long	i;

	nb = n;
	i = 0;
	resu = malloc(sizeof(char) * check_size(nb) + 1);
	if (resu == NULL)
		return (NULL);
	i = check_size(nb) - 1;
	resu[i + 1] = '\0';
	if (nb == 0)
		resu[0] = '0';
	if (nb < 0)
	{
		resu[0] = '-';
		nb *= (-1);
	}
	while (nb > 0)
	{
		resu[i--] = (nb % 10 + '0');
		nb /= 10;
	}
	return (resu);
}
/*
int	main(int ac, char **av)
{
	printf("%s\n", ft_itoa(atoi(av[1])));
	return (0);
}*/
