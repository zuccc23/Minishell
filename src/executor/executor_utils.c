#include "../../include/minishell.h"

void free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->envp)
	 	free_strs(exec->envp);
	if (exec->pidarray)
	{
		free(exec->pidarray);
		exec->pidarray = NULL;
	}
	if (exec->infile_fd != -1)
		safe_close(&exec->infile_fd);
	if (exec->outfile_fd != -1)
		safe_close(&exec->outfile_fd);
	if (exec->pipe_fd[0] != -1)
		safe_close(&exec->pipe_fd[0]);
	if (exec->pipe_fd[1] != -1)
		safe_close(&exec->pipe_fd[1]);
	free(exec);
}

// Initialiser la structure de lexec
int init_exec(t_exec *exec, t_command *cmd)
{
	exec->count_cmd = count_commands(cmd);
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->input_fd = STDIN_FILENO;
	exec->output_fd = STDOUT_FILENO;
	exec->infile_fd = -1;
	exec->outfile_fd = -1;
	exec->last_exit_status = 0;
	if (exec->pidarray)
	{
		free(exec->pidarray);
		exec->pidarray = NULL;
	}
	exec->pidarray = malloc(sizeof(pid_t) * exec->count_cmd);
	if (!exec->pidarray)
	{
		free(exec->envp);
		exec->envp = NULL;
		return (-1);
	}
	return (0);
}
