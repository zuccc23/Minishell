#include "../../include/minishell.h"

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
}

// Lit l'entrée utilisateur jusqu'au délimiteur et écrit dans le pipe
void	process_hd_input(int fd, const char *delimiter, t_data shell)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if ((ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			&& line[ft_strlen(delimiter)] == '\0')
		{
			free(line);
			break ;
		}
		expanded = expand_variables(line, shell);
		write_heredoc_line(fd, line, expanded);
		free(line);
	}
}

// Routine du processus enfant pour gérer les signaux et traiter heredoc
void	heredoc_child_routine(t_data shell, const char *delimiter, int *pipe_fd)
{
	close_all_heredoc_fds(shell.command);
	signal(SIGINT, heredoc_handle_signal);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	process_hd_input(pipe_fd[1], delimiter, shell);
	close(pipe_fd[1]);
	free_commands(shell.command);
	free_exec(shell.exec);
	rl_clear_history();
}

// Ferme les deux extrémités d'un pipe (lecture et écriture)
static void	close_pipe_ends(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

// Crée un processus enfant pour gérer un heredoc et retourne le fd
int	handle_heredoc(t_data shell, char *delimiter, int *heredoc_fd)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close_pipe_ends(pipe_fd);
		return (-1);
	}
	if (pid == 0)
	{
		heredoc_child_routine(shell, delimiter, pipe_fd);
		if (g_signal == SIGINT)
			exit(130);
		exit(0);
	}
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (is_heredoc_interrupted(status, pipe_fd[0]))
		return (-1);
	*heredoc_fd = pipe_fd[0];
	return (0);
}
