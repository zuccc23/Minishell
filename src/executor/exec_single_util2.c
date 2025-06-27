#include "../../include/minishell.h"

// Prépare l'exécution : gère les builtins parent et résout le chemin
// Retourne : 0 = continuer avec fork, autre = retourner ce code
int	prepare_command_execution(t_command *cmd, t_exec *exec, char **path)
{
	int	result;

	if (is_builtin(cmd->args[0]) != NOT_BUILTIN
		&& is_parent_builtin(cmd->args[0]))
	{
		if (apply_redirection(cmd, exec) == -1)
			return (1);
		result = exec_builtins(cmd, &exec->envp, exec->last_exit_status);
		exec->last_exit_status = result;
		return (exec->last_exit_status);
	}
	if (is_builtin(cmd->args[0]) == NOT_BUILTIN)
	{
		if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], X_OK) == 0)
			*path = ft_strdup(cmd->args[0]);
		else
			*path = get_path(cmd, exec->envp);
		if (!*path)
		{
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			return (127);
		}
	}
	return (0);
}

// Attend le processus enfant avec gestion des signaux
int	wait_for_child(int pid, int *wstatus)
{
	while (waitpid(pid, wstatus, 0) == -1)
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
	return (0);
}

// Détermine le code de sortie basé sur le statut du processus
int	get_exit_status_from_wstatus(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	else
		return (1);
}

// Nettoie les FDs du parent après l'exécution
void	cleanup_parent_fds(t_exec *exec)
{
	if (exec->infile_fd != -1)
	{
		safe_close(&exec->infile_fd);
		exec->infile_fd = -1;
	}
}

// Gère tout le processus parent
int	handle_parent_process(int pid, t_exec *exec)
{
	int	wstatus;

	wait_for_child(pid, &wstatus);
	exec->last_exit_status = get_exit_status_from_wstatus(wstatus);
	cleanup_parent_fds(exec);
	return (exec->last_exit_status);
}
