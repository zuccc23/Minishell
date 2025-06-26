#include "../../include/minishell.h"

int handle_heredoc(t_data shell, const char *delimiter, int *heredoc_fd)
{
	int		pipe_fd[2];
	char	*line;
	int		status;
	pid_t	pid;

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
		close_all_heredoc_fds(shell.command);
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
			char *expanded = expand_variables(line, shell);
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
		free_commands(shell.command);
		free_exec(shell.exec);
		rl_clear_history();
		if (g_signal == SIGINT)
			exit(130);
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
		printf("\n");
		close(STDIN_FILENO);
		g_signal = SIGINT;
	}
}

int	collect_all_heredocs(t_data shell)
{
	t_redirection	*redir;
	int				heredoc_fd;

	heredoc_fd = 0;
	while (shell.command)
	{
		redir = shell.command->redirections;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				if (handle_heredoc(shell, redir->file, &heredoc_fd) == -1)
				{
					close_all_heredoc_fds(shell.command);
					return (-1);
				}
				if (redir->fd >= 0)
					close(redir->fd);
				redir->fd = heredoc_fd;
			}
			redir = redir->next;
		}
		shell.command = shell.command->next;
	}
	return (0);
}//at Makefile | grep l | ls | export po=123 > out4 > out9>ouy9

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
