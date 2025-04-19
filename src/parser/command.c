#include "../../include/minishell.h"

//recupere toutes les commandes et leurs redirections
t_command	*get_commands(t_token *token)
{
	t_command	*commands;
	t_command	*head;

	commands = new_command(token, count_args(token));
	if (!commands)
		return (NULL);
	head = commands;
	while (token)
	{
		while (is_pipe(token) == 0)
			token = token->next;
		if (token)
		{
			token = token->next;
			commands->next = new_command(token, count_args(token));
			if (!(commands->next))
				return (NULL);
			commands = commands->next;
		}
	}
	return (head);
}

// creer un noeud pour une nouvelle commande
t_command	*new_command(t_token *token, int args_count)
{
	t_command	*new_command;
	int			i;

	i = 0;
	new_command = alloc_command(args_count);
	if (!new_command)
		return (NULL);
	while (is_pipe(token) == 0)
	{
		while (is_word(token) == 1)
		{
			new_command->args[i] = ft_strdup(token->value);
			if (!(new_command->args[i]))
				return (NULL);
			token = token->next;
			i++;
		}
		assign_redirections(&token, &new_command);
	}
	if (new_command->args)
		new_command->args[i] = NULL;
	new_command->next = NULL;
	return (new_command);
}

//ajoute les redirections en addback
int	assign_redirections(t_token **token, t_command **command)
{
	t_redirection *redir_tail;

	if (is_operator(*token) == 1)
	{
		if (!(*command)->redirections)
		{
			(*command)->redirections = get_redirections(&(*token));
			if (!(*command)->redirections)
				return (ER_MALLOC);
			return (0);
		}
		redir_tail = lstlast_redir((*command)->redirections);
		redir_tail->next = get_redirections(&(*token));
		if (!(redir_tail->next))
			return (ER_MALLOC);
	}
	return (0);
}

//check le type de redirection et lui associe le bon fichier
t_redirection	*get_redirections(t_token **token)
{
	t_redirection	*redir;

	if (!(*token))
		return (NULL);
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	if ((*token)->type == TOKEN_REDIRECT_OUT)
		redir->type = REDIR_OUTPUT;
	if ((*token)->type == TOKEN_REDIRECT_IN)
		redir->type = REDIR_INPUT;
	if ((*token)->type == TOKEN_REDIRECT_APPEND)
		redir->type = REDIR_APPEND;
	if ((*token)->type == TOKEN_HEREDOC)
		redir->type = REDIR_HEREDOC;
	redir->file = ft_strdup((*token)->next->value);
	if (!redir->file)
		return (NULL);
	(*token) = (*token)->next;
	(*token) = (*token)->next;
	redir->next = NULL;
	return (redir);
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
t_command	*alloc_command(int args_count)
{
	t_command	*command;

	command = NULL;
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	if (args_count < 1)
		command->args = NULL;
	else
	{
		command->args = malloc(sizeof(char *) * args_count + 1);
		if (!(command->args))
			return (NULL);
	}
	return (command);
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
