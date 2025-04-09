/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:53:30 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/04/09 14:57:05 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(char c, unsigned int nb)
{
	char				*str;
	int					count;

	count = 0;
	if (c == 'x')
		str = "0123456789abcdef";
	else
		str = "0123456789ABCDEF";
	if (nb >= 16)
		count += ft_putnbr_hex(c, (nb / 16));
	count += ft_putlchar(str[nb % 16]);
	return (count);
}
