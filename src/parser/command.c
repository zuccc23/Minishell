#include "../../include/minishell.h"

//recupere toutes les commandes et leurs redirections
int	get_commands(t_token *token, t_command **commands)
{
	t_command	*commands_temp;

	commands_temp = NULL;
	new_command(token, &commands_temp, count_args(token));
	*commands = commands_temp;
	if (!commands_temp)
		return (ER_MALLOC);
	while (token)
	{
		while (is_pipe(token) == 0)
			token = token->next;
		if (token)
		{
			token = token->next;
			new_command(token, &(commands_temp->next), count_args(token));
			if (!(commands_temp->next))
				return (ER_MALLOC);
			commands_temp = commands_temp->next;
		}
	}
	return (ER_OK);
}

// creer un noeud pour une nouvelle commande
int	new_command(t_token *token, t_command **command, int args_count)
{
	t_command	*new_command;
	int			i;

	i = 0;
	alloc_command(&new_command, args_count);
	*command = new_command;
	if (!new_command)
		return (ER_MALLOC);
	new_command->redirections = NULL;
	while (is_pipe(token) == 0)
	{
		while (is_word(token) == 1)
		{
			new_command->args[i] = ft_strdup(token->value);
			if (!(new_command->args[i]))
				return (ER_MALLOC);
			token = token->next;
			i++;
		}
		assign_redirections(&token, &new_command);
	}
	if (new_command->args)
		new_command->args[i] = NULL;
	new_command->next = NULL;
	return (ER_OK);
}

// compte le nombre d'arguments par commande pour malloc la commande
int	count_args(t_token *token)
{
	int	count;

	if (!token)
		return (0);
	count = 0;
	while (is_pipe(token) == 0)
	{
		while (is_word(token) == 1)
		{
			count++;
			token = token->next;
		}
		if (is_operator(token) == 1)
		{
			token = token->next;
			token = token->next;
		}
	}
	return (count);
}

//malloc une commande
int	alloc_command(t_command **command, int args_count)
{
	t_command	*temp_command;

	temp_command = NULL;
	temp_command = malloc(sizeof(t_command));
	*command = temp_command;
	if (!temp_command)
		return (ER_MALLOC);
	if (args_count < 1)
		temp_command->args = NULL;
	else
	{
		temp_command->args = malloc(sizeof(char *) * (args_count + 1));
		if (!(temp_command->args))
			return (ER_MALLOC);
	}
	return (ER_OK);
}
