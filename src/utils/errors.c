/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:37:41 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:37:42 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//prints 3 strings on STDERR
void	putstr_err(char *s1, char *s2, char *s3)
{
	while (*s1)
	{
		write(STDERR_FILENO, &*s1, 1);
		s1++;
	}
	while (*s2)
	{
		write(STDERR_FILENO, &*s2, 1);
		s2++;
	}
	while (*s3)
	{
		write(STDERR_FILENO, &*s3, 1);
		s3++;
	}
}
