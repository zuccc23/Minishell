#include "../../include/minishell.h"

// Ferme les FDs du parent après le fork
void	clean_parent_fds(t_exec *exec)
{
	if (exec->input_fd != STDIN_FILENO)
		safe_close(&exec->input_fd);
	if (exec->infile_fd != -1)
	{
		safe_close(&exec->infile_fd);
		exec->infile_fd = -1;
	}
}

// Setup les pipes pour la prochaine commande
void	setup_next_pipe(t_command *cmd, t_exec *exec)
{
	if (cmd->next)
	{
		safe_close(&exec->pipe_fd[1]);
		exec->input_fd = exec->pipe_fd[0];
	}
	else
		exec->input_fd = STDIN_FILENO;
}

// Gère les pipes côté parent
void	handle_parent_pipes(t_command *cmd, t_exec *exec)
{
	clean_parent_fds(exec);
	setup_next_pipe(cmd, exec);
}

// Met à jour le statut de sortie si c'est la dernière commande
void	update_exit_status_if_last(t_exec *exec, int j, int i, int wstatus)
{
	if (j == i)
	{
		if (WIFEXITED(wstatus))
			exec->last_exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exec->last_exit_status = 128 + WTERMSIG(wstatus);
		else
			exec->last_exit_status = 1;
	}
}

// Attend tous les processus enfants du pipeline
void	wait_all_children(t_exec *exec, int i)
{
	int	j;
	int	wstatus;

	j = 0;
	while (j <= i)
	{
		wait_single_child(exec, j, &wstatus);
		update_exit_status_if_last(exec, j, i, wstatus);
		j++;
	}
}
