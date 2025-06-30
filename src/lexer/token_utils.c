/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:35:47 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:49:20 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_type	get_operator_type(t_lexer *lexer)
{
	if (lexer->current == '|')
		return (TOKEN_PIPE);
	else if (lexer->current == '>' && peek(lexer) != '>')
		return (TOKEN_REDIRECT_OUT);
	else if (lexer->current == '>' && peek(lexer) == '>')
		return (TOKEN_REDIRECT_APPEND);
	else if (lexer->current == '<' && peek(lexer) != '<')
		return (TOKEN_REDIRECT_IN);
	else if (lexer->current == '<' && peek(lexer) == '<')
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

int	extract_word_length(t_lexer *lexer)
{
	int		i;
	char	quote;
	char	c;

	i = 0;
	quote = 0;
	while (lexer->pos + i < lexer->length)
	{
		c = lexer->input[lexer->pos + i];
		if (is_quote(c))
		{
			if (quote == 0)
				quote = c;
			else if (quote != 0 && c == quote)
				quote = 0;
			i++;
			continue ;
		}
		if (quote == 0 && (c == ' ' || c == '\t' || is_delimiter_start(c)))
			break ;
		i++;
	}
	return (i);
}

// Fonction qui centralise la liberation de memoire pour tokenize
void	*free_tok_error(t_lexer **lex, t_token **h, char **value, char **p_inpu)
{
	if (*lex)
		free(*lex);
	*lex = NULL;
	if (*h)
		ft_free_list(*h);
	*h = NULL;
	if (*p_inpu)
		free(*p_inpu);
	*p_inpu = NULL;
	if (value && *value)
		free(*value);
	if (value)
		*value = NULL;
	return (NULL);
}

// Creation du token pour les types OPERATOR
t_token	*create_operator_token(t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	token->word = NULL;
	return (token);
}

// Creation du token pour les types WORD
t_token	*create_word_token(t_token_type type, t_word *word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	token->word = word;
	return (token);
}
