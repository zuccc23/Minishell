#include "../../include/minishell.h"

int handle_heredoc(t_command *cmd, const char *delimiter, int *heredoc_fd, int *exit_code, char **env)
{
	int		pipe_fd[2];
	char	*line;
	int		status;
	pid_t	pid;

	// (void)exit_code;
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close_all_heredoc_fds(cmd);
		signal(SIGINT, heredoc_handle_signal);
		signal(SIGQUIT, SIG_IGN);
		close(pipe_fd[0]);
		while (1)
		{
			line = readline("> ");
			//line = expand_variables(line, env, );
			if (!line)
				break ;
			if ((ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
				&& line[ft_strlen(delimiter)] == '\0')
			{
				free(line);
				break;
			}
			// write(pipe_fd[1], line, ft_strlen(line));
			// write(pipe_fd[1], "\n", 1);
			char *expanded = expand_variables(line, env, *exit_code);
			if (expanded)
			{
				write(pipe_fd[1], expanded, ft_strlen(expanded));
				write(pipe_fd[1], "\n", 1);
				free(expanded);
			}
			else
			{
				write(pipe_fd[1], line, ft_strlen(line));
				write(pipe_fd[1], "\n", 1);
			}
			free(line);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	// Vérifier si le processus enfant a été interrompu par un signal
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	// Vérifier si le processus enfant a échoué
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	*heredoc_fd = pipe_fd[0];
	return (0);
}

void	heredoc_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write (STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

int	collect_all_heredocs(t_command *cmd, int *exitcode, char **env)
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
				if (handle_heredoc(cmd, redir->file, &heredoc_fd, exitcode, env) == -1)
					return (-1);
				if (redir->fd >= 0)
					close(redir->fd);
				redir->fd = heredoc_fd;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

void	close_all_heredoc_fds(t_command *cmd)
{
	t_redirection *redir;

	while (cmd)
	{
		redir = cmd->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->fd >= 0)
				safe_close(&redir->fd);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
