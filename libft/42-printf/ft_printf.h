/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:57:57 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/04/09 14:57:22 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_putlchar(char c);
int	ft_putlstr(const char *s);
int	ft_putnbr(int n);
int	ft_putnbr_hex(char c, unsigned int nb);
int	ft_putnbr_u(unsigned int n);
int	ft_ptr(void *adress);
int	ft_printf(const char *format, ...);

#endif