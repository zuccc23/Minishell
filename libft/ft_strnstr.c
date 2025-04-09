/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:39:37 by mdodevsk          #+#    #+#             */
/*   Updated: 2024/11/13 15:45:10 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			i;
	size_t			j;

	j = 0;
	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *) &big[i]);
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}
/*
int main(void)
{
    const char *str = "bakamario";
    const char *strr = "";
    size_t len = 5;
    //printf("%s\n", ft_strnstr(str, strr, len));
    //printf("%s\n", strnstr(str, strr, len));
    return (0);
}*/
