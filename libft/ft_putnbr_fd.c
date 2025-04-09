/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:25:45 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/14 17:05:08 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd((nb % 10 + '0'), fd);
	}
	if (nb <= 9 && nb >= 0)
		ft_putchar_fd((nb % 10 + '0'), fd);
}
/*
int main(void)
{
    // Test avec un nombre positif
    ft_putnbr_fd(123, 1); // Attendu : 123
    write(1, "\n", 1);

    // Test avec un nombre négatif
    ft_putnbr_fd(-456, 1); // Attendu : -456
    write(1, "\n", 1);

    // Test avec zéro
    ft_putnbr_fd(0, 1); // Attendu : 0
    write(1, "\n", 1);

    // Test avec le plus grand int positif
    ft_putnbr_fd(2147483647, 1); // Attendu : 2147483647
    write(1, "\n", 1);

    // Test avec le plus petit int négatif
    ft_putnbr_fd(-2147483648, 1); // Attendu : -2147483648
    write(1, "\n", 1);

    return 0;
}*/
