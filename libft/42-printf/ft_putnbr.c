/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:53:30 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/25 12:17:54 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	long	nb;
	int		count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		count++;
	}
	if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putlchar((nb % 10 + '0'));
	}
	else
		count += ft_putlchar((nb % 10 + '0'));
	return (count);
}
