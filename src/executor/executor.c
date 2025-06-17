#include "../../include/minishell.h"

// Passer de la structure a un char** pour execve
char	**lst_to_char_star(t_env *env)
{
	int		size;
	int		i;
	char	**envp;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	i = 0;
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	while (i < size)
	{
		envp[i++] = env->value;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	apply_redirection(t_command *cmd, t_exec *exec)
{
	t_redirection	*redir;
	int				fd;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == REDIR_INPUT)
		{
			fd = open(redir->file, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("failed opening infile", 2);
				exec->last_exit_status = 1;
				return (-1);
			}
			if (exec->infile_fd != -1)
				safe_close(&exec->infile_fd);
			exec->infile_fd = fd;
		}
		else if (redir->type == REDIR_OUTPUT)
		{
			printf("Opening outfile: %s\n", redir->file);
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				ft_putstr_fd("erreur ouverture outfile", 2);
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
				ft_putstr_fd("erreur ouverture append", 2);
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
			    ft_putstr_fd("heredoc error\n", STDERR_FILENO);
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
	int		pid;
	char	*path;
	int		wstatus;

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
	if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], X_OK) == 0)
		path = ft_strdup(cmd->args[0]);
	else
		path = get_path(cmd, exec->envp);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exec->last_exit_status = 127;
		return (exec->last_exit_status);
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
		if (apply_redirection(cmd, exec) == -1)
		{
			perror("redirection failed");
			free(path);
			return (-1);
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
		execve(path, cmd->args, exec->envp);
		perror("execve failed");
		free(path);
		exit(127);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		exec->last_exit_status = WEXITSTATUS(wstatus);
		if (exec->infile_fd != -1)
		{
			safe_close(&exec->infile_fd);
			exec->infile_fd = -1;
		}
	}
	free(path);
	//free_exec(exec);
	return (0);
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

	i = -1;
	while (cmd)
	{
		path = get_path(cmd, exec->envp);
		if (!path)
		{
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exec->last_exit_status = 127;
			return (127);
		}
		if (cmd->next)
		{
			if (pipe(exec->pipe_fd) == -1)
			{
				perror("pipe");
				exec->last_exit_status = 1;
				return (-1);
			}
		}
		exec->pidarray[++i] = fork();
		if (exec->pidarray[i] < 0)
		{
			perror("fork");
			exec->last_exit_status = 1;
			free(path);
			return (-1);
		}
		else if (exec->pidarray[i] == 0)
		{
			// Child
			if (apply_redirection(cmd, exec) == -1)
			{
				perror("redirection failed");
				free_exec(exec);
				free(path);
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
			execve(path, cmd->args, exec->envp);
			perror("execve failed");
			exit(127);
		}
		else
		{
			// Parent
			free(path);

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
		waitpid(exec->pidarray[j], &wstatus, 0);
		if (j == i)
			exec->last_exit_status = WEXITSTATUS(wstatus);
		j++;
	}
	//free_exec(exec);
	return (0);
}

// Fonction principale qui orchestre toute lexec
int	execute(t_command *command, t_env *env)
{
	int		error_code;
	t_exec	exec;

	error_code = init_exec(env, &exec, command);
	if (error_code != ER_OK)
		return (error_code);
	error_code = collect_all_heredocs(command, &exec.last_exit_status, env);
	if (error_code != ER_OK)
	{
		exec.last_exit_status = error_code;
		free_exec(&exec);
		return (error_code);
	}
	if (!command->args || !command->args[0])
	{
		if (!has_valid_redirections(command))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", STDERR_FILENO);
			exec.last_exit_status = 2;
			free_exec(&exec);
			return (2);
		}
	}
	if (command->next == NULL)
		error_code = execute_single_command(command, &exec);
	else
		error_code = execute_pipeline(command, &exec);
	close_all_heredoc_fds(command);
	free_exec(&exec);
	return (error_code);
}
