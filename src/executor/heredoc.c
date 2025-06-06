#include "../../include/minishell.h"

int	has_valid_redirections(t_command *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT ||
			redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int handle_heredoc(const char *delimiter, int *heredoc_fd)
{
	int		pipe_fd[2];
	char	*line;
	int		status;
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		while (1)
		{
			line = readline("> ");
			if (!line || ((ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			&& line[ft_strlen(delimiter) == '\0']))
			{
				free(line);
				break;
			}
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);
			free(line);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		close(pipe_fd[0]);
		return (-1);
	}
	*heredoc_fd = pipe_fd[0];
	return (0);
}

int	collect_all_heredocs(t_command *cmd)
{
	t_redirection	*redir;
	int				heredoc_fd;

	heredoc_fd = 0;
	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (handle_heredoc(redir->file, &heredoc_fd) == -1)
					return (-1);
				redir->fd = heredoc_fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
