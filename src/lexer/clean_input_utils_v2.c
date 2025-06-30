/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input_utils_v2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:35:08 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:35:09 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//get word inside double quotes
int	get_word_dq(t_word **word, char *input, int *i)
{
	int	a;

	a = 0;
	(*word) = new_word(count_word_size(input, *i));
	if (!(*word))
		return (-1);
	(*word)->expandable = 0;
	(*i)++;
	while (is_double_quotes(input[*i]) == 0)
	{
		if (is_expandable(input[*i], input[(*i) + 1]) == 1)
			(*word)->expandable = 1;
		(*word)->value[a++] = input[(*i)++];
	}
	(*i)++;
	(*word)->value[a++] = '\0';
	return (0);
}

//get word inside single quotes
int	get_word_sq(t_word **word, char *input, int *i)
{
	int	a;

	a = 0;
	(*word) = new_word(count_word_size(input, *i));
	if (!(*word))
		return (-1);
	(*word)->expandable = 0;
	(*i)++;
	while (is_single_quotes(input[*i]) == 0)
		(*word)->value[a++] = input[(*i)++];
	(*i)++;
	(*word)->value[a++] = '\0';
	return (0);
}

//get word inside no quotes
int	get_word_nq(t_word **word, char *input, int *i)
{
	int	a;

	a = 0;
	(*word) = new_word(count_word_size(input, *i));
	if (!(*word))
		return (-1);
	(*word)->expandable = 0;
	while (is_ok_word(input[*i]) == 1)
	{
		if (is_expandable(input[*i], input[(*i) + 1]) == 1)
			(*word)->expandable = 1;
		(*word)->value[a++] = input[(*i)++];
	}
	(*word)->value[a++] = '\0';
	return (0);
}

//verifie que les quotes ne sont pas vides
int	check_empty_quotes(char c, char c_next)
{
	if (c == '"' && c_next == '"')
		return (1);
	if (c == '\'' && c_next == '\'')
		return (1);
	else
		return (0);
}

//compte la taille d'un morceau de mot
int	count_word_size(char *input, int i)
{
	int	count;

	count = 0;
	if (is_double_quotes(input[i]) == 1)
	{
		i++;
		while (is_double_quotes(input[i++]) == 0)
			count++;
	}
	else if (is_single_quotes(input[i]) == 1)
	{
		i++;
		while (is_single_quotes(input[i++]) == 0)
			count++;
	}
	else if (is_ok_word(input[i]) == 1)
	{
		while (is_ok_word(input[i++]) == 1)
			count++;
	}
	return (count);
}
