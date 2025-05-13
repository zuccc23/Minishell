#include "../../include/minishell.h"

void	free_commands(t_command *commands)
{
	t_command	*temp;

	while (commands)
	{
		if (commands->args)
			free_strs(commands->args);
		if (commands->redirections)
			free_redirections(commands->redirections);
		temp = commands;
		commands = commands->next;
		free(temp);
		temp = NULL;
	}
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

void	free_redirections(t_redirection *redir)
{
	t_redirection	*temp;

	if (!redir)
		return ;
	while (redir)
	{
		if (redir->file)
			free(redir->file);
		temp = redir;
		redir = redir->next;
		free(temp);
		temp = NULL;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*temp;
	t_word	*wrd_tmp;

	if (!token)
		return ;
	while (token)
	{
		if (token->value)
			free(token->value);
		while (token->word)
		{
			wrd_tmp = token->word;
			free(token->word->value);
			token->word = token->word->next;
			free(wrd_tmp);
		}
		temp = token;
		token = token->next;
		free(temp);
		temp = NULL;
	}
}
