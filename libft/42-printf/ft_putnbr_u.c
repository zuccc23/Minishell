/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:53:30 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/23 17:05:46 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_u(unsigned int n)
{
	unsigned long	nb;
	int				count;

	nb = (unsigned long)n;
	count = 0;
	if (nb > 9)
	{
		count += ft_putnbr_u(nb / 10);
		count += ft_putlchar((nb % 10 + '0'));
	}
	else
		count += ft_putlchar((nb % 10 + '0'));
	return (count);
}
