#include "../../include/minishell.h"

//imprime la valeur entiere du token (localisee dans t_word)
void	print_token_value(t_word *word, t_token *token)
{
	t_word	*head;

	head = word;
	ft_printf("`");
	while (word)
	{
		ft_printf("%s", word->value);
		word = word->next;
	}
	if (token->type == TOKEN_REDIRECT_IN)
		ft_printf("<");
	if (token->type == TOKEN_REDIRECT_OUT)
		ft_printf(">");
	if (token->type == TOKEN_HEREDOC)
		ft_printf("<<");
	if (token->type == TOKEN_REDIRECT_APPEND)
		ft_printf(">>");
	ft_printf("'\n");
	word = head;
}

// fonction pour regarder si ya un operateur tt seul (erreur)
int	check_single_operator(t_token *token)
{
	if (!token->next)
	{
		if (is_pipe(token) == 1)
		{
			ft_printf("minishell: syntax error near unexpected token `|'\n");
			return (ER_SINGLE_OPERATOR);
		}
		if (is_word(token) != 1)
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

	if (is_pipe(token) == 1)
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
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
				ft_printf("minishell: ");
				ft_printf("syntax error near unexpected token `|'\n");
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
				ft_printf("minishell: ");
				if (!next)
					ft_printf("syntax error near unexpected token `newline'\n");
				else
				{
					ft_printf("syntax error near unexpected token ");
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
				ft_printf("minishell: ");
				ft_printf("syntax error near unexpected token `newline'\n");
				return (ER_OPERATOR_SYNTAX);
			}
		}
		token = token->next;
	}
	return (ER_OK);
}
