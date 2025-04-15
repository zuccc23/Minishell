#include "../../include/minishell.h"

//recupere toutes les commandes
t_command	*get_commands(t_token *token)
{
	t_command	*commands;
	t_command	*head;

	commands = NULL;
	commands = new_command(token, count_args(token));
	if (!commands)
		return (NULL);
	head = commands;

	while (token)
	{
		while (token && token->type != TOKEN_PIPE)
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
	while (is_pipe(token) == 0)
	{
		while (is_word(token) == 1)
		{
			new->args[i] = ft_strdup(token->value);
			if (!(new->args[i]))
				return (NULL);
			token = token->next;
			i++;
		}
		// if (is_operator(token) == 1)
		// {
		// 	new->redirections = get_redirections(&token);
		// }
	}
	// while (is_word(token) == 1)
	// {
	// 	new->args[i] = ft_strdup(token->value);
	// 	if (!(new->args[i]))
	// 		return (NULL);
	// 	token = token->next;
	// 	i++;
	// }
	new->args[i] = NULL;
	new->next = NULL;
	return (new);
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
	return (redir);
}

// compte le nombre d'arguments par commande pour malloc
int	count_args(t_token *token)
{
	int count;

	if (!token)
		return (0);
	count = 0;
	while (is_word(token) == 1)
	{
		count++;
		token = token->next;
	}
	return (count);
}

// t_command	*idk(t_token *token, int command_count)
// {
// 	t_command	*command;

// 	command = new_command(token, command_count);
// 	command->redirections =

// 	return (command);
// }

// t_command	*new_command(t_token *token, int command_count)
// {
// 	t_command	*new;
// 	int			i;

// 	new = NULL;
// 	i = 0;
// 	new = malloc(sizeof(t_command));
// 	if (!new)
// 		return (NULL);
// 	new->args = malloc(sizeof(char *) * command_count + 1);
// 	if (!(new->args))
// 		return (NULL);
// 	while (is_word(token) == 1)
// 	{
// 		new->args[i] = ft_strdup(token->value);
// 		if (!(new->args[i]))
// 			return (NULL);
// 		token = token->next;
// 		i++;
// 	}
// 	new->args[i] = NULL;
// 	new->next = NULL;
// 	return (new);
// }