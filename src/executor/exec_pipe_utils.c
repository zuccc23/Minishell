/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:33:12 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:33:13 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Setup du pipe si la commande suivante existe
void	setup_pipe_if_needed(t_command *cmd, t_exec *exec)
{
	if (cmd->next)
	{
		if (pipe(exec->pipe_fd) == -1)
		{
			perror("pipe");
			return ;
		}
	}
}

// Fork une nouvelle commande et stocke le PID
void	fork_command(t_exec *exec, int *i)
{
	exec->pidarray[++(*i)] = fork();
	if (exec->pidarray[*i] < 0)
	{
		perror("fork");
		return ;
	}
}

// Setup des redirections dans le processus enfant
void	set_child_in_redir(t_command *cmd, t_exec *exec, t_command *cmd_h)
{
	handle_child_signal();
	if (apply_redirection(cmd, exec) == -1)
	{
		if (exec->input_fd != STDIN_FILENO)
			safe_close(&exec->input_fd);
		free_commands(cmd_h);
		rl_clear_history();
		free_exec(exec);
		exit(1);
	}
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
}

// Setup des pipes de sortie dans le processus enfant
void	set_child_out_pipe(t_command *cmd, t_exec *exec, t_command *cmd_h)
{
	if (cmd->next)
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
		safe_close(&exec->pipe_fd[1]);
		safe_close(&exec->pipe_fd[0]);
	}
	if (apply_redirection(cmd, exec) == -1)
	{
		if (exec->input_fd != STDIN_FILENO)
			safe_close(&exec->input_fd);
		free_commands(cmd_h);
		rl_clear_history();
		free_exec(exec);
		exit(1);
	}
	if (exec->outfile_fd != -1)
	{
		dup2(exec->outfile_fd, STDOUT_FILENO);
		safe_close(&exec->outfile_fd);
	}
}

// Initialise les variables pour l'exécution du pipeline
void	init_pipe_var(int *i, char **path)
{
	*i = -1;
	*path = NULL;
	handle_exec_signal();
}
