#include "../../include/minishell.h"

//recupere toutes les commandes et leurs redirections
int	get_commands(t_token *token, t_command **commands)
{
	t_command	*commands_temp;

	commands_temp = NULL;
	new_command(token, &commands_temp, count_args(token));
	if (!commands_temp)
		return (ER_MALLOC);
	*commands = commands_temp;
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
	if (!new_command)
		return (ER_MALLOC);
	*command = new_command;
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

//ajoute les redirections en addback
int	assign_redirections(t_token **token, t_command **command)
{
	t_redirection *redir_tail;

	if (is_operator(*token) == 1)
	{
		if (!(*command)->redirections)
		{
			get_redirections(&(*token), &(*command)->redirections);
			if (!(*command)->redirections)
				return (ER_MALLOC);
			return (0);
		}
		redir_tail = lstlast_redir((*command)->redirections);
		get_redirections(&(*token), &redir_tail->next);
		if (!(redir_tail->next))
			return (ER_MALLOC);
	}
	return (0);
}

//check le type de redirection et lui associe le bon fichier
int	get_redirections(t_token **token, t_redirection **redir)
{
	t_redirection	*temp_redir;

	temp_redir = malloc(sizeof(t_redirection));
	if (!temp_redir)
		return (ER_MALLOC);
	*redir = temp_redir;
	if ((*token)->type == TOKEN_REDIRECT_OUT)
		temp_redir->type = REDIR_OUTPUT;
	if ((*token)->type == TOKEN_REDIRECT_IN)
		temp_redir->type = REDIR_INPUT;
	if ((*token)->type == TOKEN_REDIRECT_APPEND)
		temp_redir->type = REDIR_APPEND;
	if ((*token)->type == TOKEN_HEREDOC)
		temp_redir->type = REDIR_HEREDOC;
	temp_redir->file = ft_strdup((*token)->next->value);
	if (!temp_redir->file)
		return (ER_MALLOC);
	(*token) = (*token)->next;
	(*token) = (*token)->next;
	temp_redir->next = NULL;
	return (ER_OK);
}

// compte le nombre d'arguments par commande pour malloc la commande
int	count_args(t_token *token)
{
	int count;

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
	if (!temp_command)
		return (ER_MALLOC);
	*command = temp_command;
	if (args_count < 1)
		temp_command->args = NULL;
	else
	{
		temp_command->args = malloc(sizeof(char *) * args_count + 1);
		if (!(temp_command->args))
			return (ER_MALLOC);
	}
	return (ER_OK);
}

//retourne le dernier noeud de la liste de redirections
t_redirection	*lstlast_redir(t_redirection *lst)
{
	t_redirection	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
