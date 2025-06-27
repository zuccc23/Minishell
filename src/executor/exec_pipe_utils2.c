#include "../../include/minishell.h"

// Exécute un builtin dans le processus enfant du pipeline
void	execute_pipe_builtin(t_command *cmd, t_exec *exec, t_command *cmd_head)
{
	int	exit_code;

	exit_code = 0;
	exit_code = exec_builtins(cmd, &exec->envp, exec->last_exit_status);
	free_commands(cmd_head);
	free_exec(exec);
	exit(exit_code);
}

// Résout le chemin d'une commande externe
char	*resolve_command_path(t_command *cmd, t_exec *exec)
{
	char	*path;

	if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], X_OK) == 0)
		path = ft_strdup(cmd->args[0]);
	else
		path = get_path(cmd, exec->envp);
	return (path);
}

// Nettoie et exit en cas d'erreur de commande
void	cleanup_exit_error(t_command *cmd, t_exec *exec, t_command *cmd_head)
{
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	if (exec->pipe_fd[0] != -1)
		safe_close(&exec->pipe_fd[0]);
	if (exec->pipe_fd[1] != -1)
		safe_close(&exec->pipe_fd[1]);
	free_commands(cmd_head);
	free_exec(exec);
	rl_clear_history();
	exit(127);
}

// Exécute une commande externe avec execve
void	exec_ext(t_command *cmd, char *path, t_exec *exec, t_command *cmd_hd)
{
	execve(path, cmd->args, exec->envp);
	perror("execve failed");
	free_commands(cmd_hd);
	free_exec(exec);
	rl_clear_history();
	free(path);
	exit(127);
}

// Gère l'exécution d'une commande externe dans le pipeline
void	execute_pipe_ext(t_command *cmd, t_exec *exec, t_command *cmd_head)
{
	char	*path;

	path = resolve_command_path(cmd, exec);
	if (!path)
		cleanup_exit_error(cmd, exec, cmd_head);
	exec_ext(cmd, path, exec, cmd_head);
}
