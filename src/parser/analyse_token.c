#include "../../include/minishell.h"

int	is_operator(t_token *token)
{
	if (!token)
		return (-1);
	if (token->type == TOKEN_REDIRECT_APPEND)
		return (1);
	else if (token->type == TOKEN_REDIRECT_IN)
		return (1);
	else if (token->type == TOKEN_REDIRECT_OUT)
		return (1);
	else if (token->type == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}

int	is_word(t_token *token)
{
	if (!token)
		return (-1);
	if (token->type == TOKEN_WORD)
		return (1);
	else
		return (0);
}

int	is_pipe(t_token *token)
{
	if (!token)
		return (-1);
	if (token->type == TOKEN_PIPE)
		return (1);
	else
		return (0);
}
