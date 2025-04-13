#include "../../include/minishell.h"

t_command	*get_commands(t_token *token)
{
	t_command	*commands;
	int			i;

	i = 0;
	commands = NULL;
	while (token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
		{
			commands->args[i] = token->value;
		}
		i++;
		//set redirections to null

	}
	return (commands);
}

// creer un noeud pour une nouvelle commande
t_command	*new_command(t_token *token, int command_count)
{
	t_command *new = NULL;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = malloc(sizeof(char *) * command_count + 1);
	if (!(new->args))
		return (NULL);
	while (token->type == TOKEN_WORD)
	{
		//
	}

	new->next = NULL;
	return (new);
}

// compte le nombre d'arguments par commande pour malloc
int	count_args(t_token *token)
{
	int count;

	count = 0;
	while (token->type == TOKEN_WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}