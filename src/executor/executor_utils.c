#include "../../include/minishell.h"

void free_exec(t_exec *exec)
{
	if (exec->envp)
		free(exec->envp);
	if (exec->pidarray)
		free(exec->pidarray);
}

// Initialiser la structure de lexec
int init_exec(t_env *env, t_exec *exec, t_command *cmd)
{
	exec->count_cmd = count_commands(cmd);
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->input_fd = STDIN_FILENO;
	exec->output_fd = STDOUT_FILENO;
	exec->infile_fd = -1;
	exec->outfile_fd = -1;
	exec->envp = lst_to_char_star(env);
	if (!exec->envp)
		return (-1);
	exec->pidarray = malloc(sizeof(pid_t) * exec->count_cmd);
	if (!exec->pidarray)
		return (-1);
	return (0);
}
