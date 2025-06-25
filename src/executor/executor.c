#include "../../include/minishell.h"

int	apply_redirection(t_command *cmd, t_exec *exec)
{
	t_redirection	*redir = NULL;
	int				fd = -1;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				putstr_err("minishell: ", redir->file, ": Permission denied\n");
				exec->last_exit_status = 1;
				exit(-1);
			}
			if (exec->infile_fd != -1)
				safe_close(&exec->infile_fd);
			exec->infile_fd = fd;
		}
		else if (redir->type == REDIR_OUTPUT)
		{
			// printf("Opening outfile: %s\n", redir->file);
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				putstr_err("minishell: ", redir->file, ": Permission denied\n");
				exec->last_exit_status = 1;
				return (-1);
			}
			if (exec->outfile_fd != -1)
				safe_close(&exec->outfile_fd);
			exec->outfile_fd = fd;
		}
		else if (redir->type == REDIR_APPEND)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				putstr_err("minishell: ", redir->file, ": Permission denied\n");
				exec->last_exit_status = 1;
				return (-1);
			}
			if (exec->outfile_fd != -1)
				safe_close(&exec->outfile_fd);
			exec->outfile_fd = fd;
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			if (redir->fd == -1)
			{
			    ft_putstr_fd("minishell: heredoc error\n", STDERR_FILENO);
				exec->last_exit_status = 1;
        		return (-1);
			}
			if (exec->infile_fd != -1)
				safe_close(&exec->infile_fd);
			exec->infile_fd = redir->fd;
		}
		redir = redir->next;
	}
	return (0);
}

// Gere le cas ou nous avons une seule commande
int	execute_single_command(t_command *cmd, t_exec *exec)
{
	int		pid = 0;
	char	*path = NULL;
	int		wstatus = 0;
	int		exit_status;

	exit_status = 0;
	path = NULL;
	if (!cmd->args || !cmd->args[0])
	{
		if (has_valid_redirections(cmd))
		{
			// Exécuter seulement les redirections sans commande
			if (apply_redirection(cmd, exec) == -1)
				return (1);
			return (0);
		}
		return (127);
	}
	//add builtins
	if (is_builtin(cmd->args[0]) != NOT_BUILTIN && is_parent_builtin(cmd->args[0]))
	{
		if (apply_redirection(cmd, exec) == -1)
			return (1);
		exec->last_exit_status = exec_builtins(cmd, &exec->envp, exec->last_exit_status);
		return (exec->last_exit_status);
	}
	if (is_builtin(cmd->args[0]) == NOT_BUILTIN)
	{
		if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], X_OK) == 0)
			path = ft_strdup(cmd->args[0]);
		else
			path = get_path(cmd, exec->envp);
		if (!path)
		{
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			return (127);
		}
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Failed fork \n");
		exec->last_exit_status = 1;
		free(path);
		return (-1);
	}
	if (pid == 0)
	{
		// child --> apply redirection
		handle_child_signal();
		if (apply_redirection(cmd, exec) == -1)
		{
			free(path);
			exit(-1);
		}

		if(exec->infile_fd != -1)
		{
			dup2(exec->infile_fd, STDIN_FILENO);
			safe_close(&exec->infile_fd);
		}
		if (exec->outfile_fd != -1)
		{
			dup2(exec->outfile_fd, STDOUT_FILENO);
			safe_close(&exec->outfile_fd);
		}
		close_all_heredoc_fds(cmd);

		//add builtins
		if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
		{
			exit_status = exec_builtins(cmd, &exec->envp, exec->last_exit_status);
			if (path)
				free(path);
			free_exec(exec);
			free_commands(cmd);
			exit(exit_status);
		}
		else
		{
			execve(path, cmd->args, exec->envp);
			perror("execve failed");
			free(path);
			exit(127);
		}
	}
	else
	{
		while (waitpid(pid, &wstatus, 0) == -1)
		{
			if (errno == EINTR)
			{
				if (g_signal == SIGINT)
				{
					kill(pid, SIGINT);
					g_signal = 0;
				}
				else
				{
					perror("waitpid");
					break;
				}
			}
		}
		//GET EXIT STATUS OF CHILD
		if (WIFEXITED(wstatus))
		{
			exec->last_exit_status = WEXITSTATUS(wstatus);
		}
		else if (WIFSIGNALED(wstatus))
		{
			// Process was terminated by signal
			exec->last_exit_status =  128 + WTERMSIG(wstatus);
		}
		else
		{
			exec->last_exit_status = 1; // Unknown termination
		}
		if (exec->infile_fd != -1)
		{
			safe_close(&exec->infile_fd);
			exec->infile_fd = -1;
		}
	}
	free(path);
	return (exec->last_exit_status);
}

// Compter le nombre de commande
int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static int	execute_pipeline(t_command *cmd, t_exec *exec)
{
	int		i;
	int		j;
	char	*path;
	int		wstatus;
	int		exit_code;
	t_command *cmd_head = cmd;

	exit_code = 0;
	i = -1;
	handle_exec_signal();
	while (cmd)
	{
		if (cmd->next)
		{
			//PIPE
			if (pipe(exec->pipe_fd) == -1)
			{
				perror("pipe");
				// exec->last_exit_status = 1;
				exit(-1);
			}
		}
		//FORK
		exec->pidarray[++i] = fork();
		if (exec->pidarray[i] < 0)
		{
			perror("fork");
			// exec->last_exit_status = 1;
			exit(-1);
		}
		else if (exec->pidarray[i] == 0)
		{
			// CHILD
			handle_child_signal();
			//REDIRECTIONS
			if (apply_redirection(cmd, exec) == -1)
			{
				free_exec(exec);
				exit(1);
			}
			// Setup input
			if (exec->infile_fd != -1)
			{
				dup2(exec->infile_fd, STDIN_FILENO);
				safe_close(&exec->infile_fd);
			}
			else if (exec->input_fd != STDIN_FILENO)
			{
				dup2(exec->input_fd, STDIN_FILENO);
				safe_close(&exec->input_fd);
			}

			// Setup output (pipe to next command)
			if (cmd->next)
			{
				dup2(exec->pipe_fd[1], STDOUT_FILENO);
				safe_close(&exec->pipe_fd[1]);
				safe_close(&exec->pipe_fd[0]);
			}

			// Setup output redir (overides pipe)
			if (exec->outfile_fd != -1)
			{
				dup2(exec->outfile_fd, STDOUT_FILENO);
				safe_close(&exec->outfile_fd);
			}
			//close_all_heredoc_fds(cmd);

			//BUILTINS
			if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
			{
				exit_code = exec_builtins(cmd, &exec->envp, exec->last_exit_status);
				free_exec(exec);
				free_commands(cmd_head);
				exit(exit_code);
			}
			else
			{
				//EXECVE
				if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], X_OK) == 0)
					path = ft_strdup(cmd->args[0]);
				else
					path = get_path(cmd, exec->envp);
				if (!path)
				{
					ft_putstr_fd(cmd->args[0], STDERR_FILENO);
					ft_putstr_fd(": command not found\n", STDERR_FILENO);
					// exec->last_exit_status = 127;
					exit(127);
				}
				execve(path, cmd->args, exec->envp);
				perror("execve failed");
				free(path);
				exit(127);
			}
		}
		else
		{
			// Parent
			// free(path);

			// Close the current input fd if not stdin
			if (exec->input_fd != STDIN_FILENO)
				safe_close(&exec->input_fd);

			// Close infile fd after child duplicated it
			if (exec->infile_fd != -1)
			{
				safe_close(&exec->infile_fd);
				exec->infile_fd = -1;
			}

			if (cmd->next)
			{
				// close write end of pipe in parent
				safe_close(&exec->pipe_fd[1]);
				// Setup for next command
				exec->input_fd = exec->pipe_fd[0];
			}
			else
				exec->input_fd = STDIN_FILENO;
		}
		cmd = cmd->next;
	}
	j = 0;
	while (j <= i)
	{
		while (waitpid(exec->pidarray[j], &wstatus, 0) == -1)
		{
			if (errno == EINTR)
			{
				if (g_signal == SIGINT)
				{
					kill(exec->pidarray[j], SIGINT);
					g_signal = 0;
				}
				continue; // Try waitpid again
			}
			else
			{
				perror("waitpid");
				break;
			}
		}

		// Only get exit status from the last command
		if (j == i)
		{
			if (WIFEXITED(wstatus))
			{
				exec->last_exit_status = WEXITSTATUS(wstatus);
			}
			else if (WIFSIGNALED(wstatus))
			{
				// Process was terminated by signal
				exec->last_exit_status =  128 + WTERMSIG(wstatus);
			}
			else
			{
				exec->last_exit_status = 1; // Unknown termination
			}
		}
		j++;
	}
	return (exec->last_exit_status);
}

// Fonction principale qui orchestre toute lexec
int	execute(t_command *command, char **env, t_exec **exec)
{
	int		error_code;

	(void)env;
	handle_exec_signal();
	error_code = init_exec(env, &(**exec), command);
	if (error_code != ER_OK)
		return (error_code);
	error_code = collect_all_heredocs(command, &(**exec).last_exit_status, env, exec);
	if (error_code != ER_OK)
	{
		(**exec).last_exit_status = error_code;
		free_exec(&(**exec));
		return (error_code);
	}
	// if (!command->args || !command->args[0])
	// {
	// 	if (!has_valid_redirections(command))
	// 	{
	// 		ft_putstr_fd("minishell: syntax error near unexpected token\n", STDERR_FILENO);
	// 		(**exec).last_exit_status = 2;
	// 		free_exec(&(**exec));
	// 		return (2);
	// 	}
	// }
	if (command->next == NULL)
		error_code = execute_single_command(command, &(**exec));
	else
		error_code = execute_pipeline(command, &(**exec));
	close_all_heredoc_fds(command);
	// free_exec(&exec);
	return (error_code);
}
