#include "../../include/minishell.h"

void	safe_close(int *fd)
{
	if (*fd != -1 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO
		&& *fd != STDERR_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
}

int	has_valid_redirections(t_command *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT
			|| redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}
