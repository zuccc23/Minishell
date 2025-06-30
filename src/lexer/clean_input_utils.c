/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:35:12 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:35:13 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	if (c == '\0')
		return (-1);
	if (c == ' ')
		return (1);
	else
		return (0);
}

int	is_double_quotes(char c)
{
	if (c == '\0')
		return (-1);
	if (c == '"')
		return (1);
	else
		return (0);
}

int	is_expandable(char c, char next_c)
{
	if (c == '\0')
		return (-1);
	if (c == '$' && next_c != '\0')
		return (1);
	else
		return (0);
}

int	is_single_quotes(char c)
{
	if (c == '\0')
		return (-1);
	if (c == '\'')
		return (1);
	else
		return (0);
}

int	is_ok_word(char c)
{
	if (c == '\0')
		return (-1);
	if (c == ' ')
		return (0);
	if (c == '"')
		return (0);
	if (c == '\'')
		return (0);
	else
		return (1);
}
