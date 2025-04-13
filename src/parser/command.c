#include "../../include/minishell.h"

//recupere toutes les commandes
t_command	*get_commands(t_token *token)
{
	t_command	*commands;
	t_command	*head;

	commands = NULL;
	commands = new_command(token, count_args(token));
	head = commands;
	while (token)
	{
		while (token && token->type != TOKEN_PIPE)
			token = token->next;
		
	}
	return (head);
}

// creer un noeud pour une nouvelle commande
t_command	*new_command(t_token *token, int command_count)
{
	t_command	*new;
	int			i;

	new = NULL;
	i = 0;
	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->args = malloc(sizeof(char *) * command_count + 1);
	if (!(new->args))
		return (NULL);
	while (token->type == TOKEN_WORD)
	{
		new->args[i] = ft_strdup(token->value);
		if (!(new->args[i]))
			return (NULL);
		token = token->next;
		i++;
	}
	new->args[i] = NULL;
	new->next = NULL;
	return (new);
}

// compte le nombre d'arguments par commande pour malloc
int	count_args(t_token *token)
{
	int count;

	if (!token)
		return (0);
	count = 0;
	while (token->type == TOKEN_WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}