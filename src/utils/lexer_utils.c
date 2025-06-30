/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:37:52 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:37:53 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Faire avancer le lexer
void	advance(t_lexer *lexer)
{
	if (lexer->pos < lexer->length)
	{
		lexer->pos++;
		lexer->current = lexer->input[lexer->pos];
	}
}

// Pour verifier le caractere suivant du lexer
char	peek(t_lexer *lexer)
{
	if (lexer->pos + 1 < lexer->length)
		return (lexer->input[lexer->pos + 1]);
	return ('\0');
}

// Saute les espaces
void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->pos < lexer->length && (lexer->current == ' '
			|| lexer->current == '\t'))
	{
		lexer->pos++;
		lexer->current = lexer->input[lexer->pos];
	}
}

//Permet de faire avancer le lexer de la taille de loperateur
int	extract_operator_value(t_lexer *lexer)
{
	t_token_type	type;
	char			*value;

	type = get_operator_type(lexer);
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIRECT_APPEND)
		value = malloc(sizeof(char) * 3);
	else
		value = malloc(sizeof(char) * 2);
	if (!value)
		return (0);
	value[0] = lexer->current;
	advance(lexer);
	if (type == TOKEN_HEREDOC || type == TOKEN_REDIRECT_APPEND)
	{
		value[1] = lexer->current;
		advance(lexer);
		value[2] = '\0';
	}
	else
		value[1] = '\0';
	free(value);
	return (1);
}
