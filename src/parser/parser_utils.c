/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:37:00 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:37:01 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//imprime la valeur entiere du token (localisee dans t_word)
void	print_token_value(t_word *word, t_token *token)
{
	t_word	*head;

	head = word;
	ft_putstr_fd("`", STDERR_FILENO);
	while (word)
	{
		ft_putstr_fd(word->value, STDERR_FILENO);
		word = word->next;
	}
	if (token->type == TOKEN_REDIRECT_IN)
		ft_putstr_fd("<", STDERR_FILENO);
	if (token->type == TOKEN_REDIRECT_OUT)
		ft_putstr_fd(">", STDERR_FILENO);
	if (token->type == TOKEN_HEREDOC)
		ft_putstr_fd("<<", STDERR_FILENO);
	if (token->type == TOKEN_REDIRECT_APPEND)
		ft_putstr_fd(">>", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	word = head;
}

// fonction pour regarder si ya un operateur tt seul (erreur)
int	check_single_operator(t_token *token)
{
	if (!token->next)
	{
		if (is_pipe(token) == 1)
		{
			ft_putstr_fd("minishell: syntax error ", STDERR_FILENO);
			ft_putstr_fd("near unexpected token `|'\n", STDERR_FILENO);
			return (ER_SINGLE_OPERATOR);
		}
		if (is_word(token) != 1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("syntax error near ", STDERR_FILENO);
			ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
			return (ER_SINGLE_OPERATOR);
		}
	}
	return (ER_OK);
}

// check if there is a command/file before a pipe
int	check_content_before_pipe(t_token *token)
{
	t_token	*prev;

	if (is_pipe(token) == 1)
	{
		ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
		ft_putstr_fd(" near unexpected token `|'\n", STDERR_FILENO);
		return (ER_PIPE_SYNTAX);
	}
	prev = token;
	token = token->next;
	while (token)
	{
		if (is_pipe(token) == 1)
		{
			if (is_word(prev) != 1)
			{
				ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
				ft_putstr_fd(" near unexpected token `|'\n", STDERR_FILENO);
				return (ER_PIPE_SYNTAX);
			}
		}
		prev = token;
		token = token->next;
	}
	return (ER_OK);
}

// fonction pour verifier qu'il y a un fichier apres un operateur
int	check_content_after_operator(t_token *token)
{
	t_token	*next;

	next = NULL;
	while (token)
	{
		next = token->next;
		if (is_operator(token) == 1)
		{
			if (is_word(next) != 1)
			{
				ft_putstr_fd("minishell: syntax error near u", STDERR_FILENO);
				if (!next)
					ft_putstr_fd("nexpected token `newline'\n", STDERR_FILENO);
				else
				{
					ft_putstr_fd("nexpected token ", STDERR_FILENO);
					print_token_value(token->next->word, token->next);
				}
				return (ER_OPERATOR_SYNTAX);
			}
		}
		token = token->next;
	}
	return (ER_OK);
}

int	check_content_after_pipe(t_token *token)
{
	t_token	*next;

	next = NULL;
	while (token)
	{
		next = token->next;
		if (is_pipe(token) == 1)
		{
			if (!next)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near ", STDERR_FILENO);
				ft_putstr_fd("unexpected token `newline'\n", STDERR_FILENO);
				return (ER_OPERATOR_SYNTAX);
			}
		}
		token = token->next;
	}
	return (ER_OK);
}
