#include "../../include/minishell.h"

// Fork et gestion d'erreur
// Retourne : 0 = succès, -1 = erreur de fork
int	handle_fork(int *pid, t_exec *exec, char *path)
{
	*pid = fork();
	if (*pid < 0)
	{
		perror("Failed fork \n");
		exec->last_exit_status = 1;
		free(path);
		return (-1);
	}
	return (0);
}

// Setup des redirections et signaux dans le processus enfant
int	setup_child_redirections(t_command *cmd, t_exec *exec, char *path)
{
	handle_child_signal();
	if (apply_redirection(cmd, exec) == -1)
	{
		free(path);
		exit(-1);
	}
	if (exec->infile_fd != -1)
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
	return (0);
}

// Exécute un builtin dans le processus enfant
void	execute_child_builtin(t_command *cmd, t_exec *exec, char *path)
{
	int	exit_status;

	exit_status = exec_builtins(cmd, &exec->envp, exec->last_exit_status);
	if (path)
		free(path);
	free_exec(exec);
	free_commands(cmd);
	exit(exit_status);
}

// Exécute une commande externe dans le processus enfant
void	execute_child_external(t_command *cmd, char *path, t_exec *exec)
{
	execve(path, cmd->args, exec->envp);
	perror("execve failed");
	free(path);
	exit(127);
}

// Gère tout le processus enfant
void	handle_child_process(t_command *cmd, t_exec *exec, char *path)
{
	setup_child_redirections(cmd, exec, path);
	if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
		execute_child_builtin(cmd, exec, path);
	else
		execute_child_external(cmd, path, exec);
}
