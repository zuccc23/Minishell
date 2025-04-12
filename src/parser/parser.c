#include "../../include/minishell.h"

// fonction pour regarder si ya un operateur tt seul (erreur)
int	check_single_operator(t_token *token)
{
	if (!token->next)
	{
		if (token->type == TOKEN_PIPE)
		{
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			return (ER_SINGLE_OPERATOR);
		}
		if (token->type != TOKEN_WORD)
		{
			ft_printf("minishell: ");
			ft_printf("syntax error near unexpected token `newline'\n");
			return (ER_SINGLE_OPERATOR);
		}
	}
	return (ER_OK);
}

// check if there is a command/file before a pipe
int	check_content_before_pipe(t_token *token)
{
	t_token	*prev;

	if (token->type == TOKEN_PIPE)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (ER_PIPE_SYNTAX);
	}
	prev = token;
	token = token->next;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			if (prev->type != TOKEN_WORD)
			{
				ft_printf("minishell: syntax error near unexpected token `|'\n");
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
	char	*s;

	next = NULL;
	while (token)
	{
		next = token->next;
		if (token->type != TOKEN_WORD && token->type != TOKEN_PIPE)
		{
			if (!next || next->type != TOKEN_WORD)
			{
				ft_printf("minishell: ");
				if (!next)
					ft_printf("syntax error near unexpected token `newline'\n");
				else
				{
					s = next->value;
					ft_printf("syntax error near unexpected token `%s'\n", s);
				}
				return (ER_OPERATOR_SYNTAX);
			}
		}
		token = token->next;
	}
	return (ER_OK);
}

//fonction qui parse les erreurs de syntaxe ds les tokens
int	parse_tokens(t_token *token)
{
	int	er_code;

	er_code = 0;
	er_code = check_single_operator(token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = check_content_before_pipe(token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = check_content_after_operator(token);
	if (er_code != ER_OK)
		return (er_code);
	return (ER_OK);
}
