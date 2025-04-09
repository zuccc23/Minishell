/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:20:19 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/25 12:55:48 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putlstr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putlstr("(null)"));
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
