#include "../../include/minishell.h"

void	free_commands(t_command *commands)
{
	while (commands)
	{
		if (commands->args)
			free_strs(commands->args);
		
		while (commands->redirections)
		{

		}
		commands = commands->next;
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
	free(strs[i]);
	free(strs);
	strs = NULL;
}
void	free_redirections(t_redirection *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		redir = redir->next;
	}
}