/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:37:55 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:37:56 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_to_list(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = *token;
	tmp = ft_token_last(*token);
	if (!tmp)
		*token = new;
	else
		tmp->next = new;
}

t_token	*ft_token_last(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

// Facilite laffichage des types de token
const char	*token_type_to_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == TOKEN_REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	else if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

// Free la liste chainee WORD
void	free_word_list(t_word *word)
{
	t_word	*tmp;

	while (word)
	{
		tmp = word->next;
		if (word->value)
			free(word->value);
		free(word);
		word = tmp;
	}
}

// Free la liste chainee TOKEN
void	ft_free_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->word)
		{
			free_word_list(token->word);
			token->word = NULL;
		}
		free(token);
		token = tmp;
	}
}
