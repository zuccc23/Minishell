/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:09:56 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/25 12:46:14 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr(void *adress)
{
	unsigned long	p;

	if (!adress)
		return (ft_putlstr("(nil)"));
	p = (unsigned long)adress;
	ft_putlstr("0x");
	return (ft_putnbr_hex('x', p) + 2);
}
