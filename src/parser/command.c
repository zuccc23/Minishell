#include "../../include/minishell.h"

t_command	*get_commands(t_token *token)
{
	t_command	*commands;

	while (token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
		{

		}
	}
	return (commands);
}
