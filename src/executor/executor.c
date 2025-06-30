/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:33:45 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:33:46 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction principale qui orchestre toute lexec
int	execute(t_data shell)
{
	int	err_code;

	err_code = 0;
	handle_exec_signal();
	err_code = init_exec(shell.exec, shell.command);
	if (err_code != ER_OK)
		return (err_code);
	err_code = collect_all_heredocs(shell);
	if (err_code != ER_OK)
	{
		shell.exec->last_exit_status = err_code;
		return (err_code);
	}
	if (shell.command->next == NULL)
		err_code = execute_single_command(shell.command, shell.exec);
	else
		err_code = execute_pipeline(shell.command, shell.exec);
	close_all_heredoc_fds(shell.command);
	return (err_code);
}

// Gere le cas ou nous avons une seule commande
int	execute_single_command(t_command *cmd, t_exec *exec)
{
	int		pid;
	char	*path;
	int		wstatus;
	int		exit_status;
	int		result;

	init_cmd_var(&pid, &path, &wstatus, &exit_status);
	result = validate_command(cmd, exec);
	if (check_result(result) != 111)
		return (check_result(result));
	result = prepare_cmd_execution(cmd, exec, &path);
	if (result != 0)
		return (result);
	if (do_fork(cmd->args[0]) == 1)
	{
		result = handle_fork(&pid, exec, path);
		if (result == -1)
			return (-1);
		if (pid == 0)
			handle_child_process(cmd, exec, path);
		else
			result = handle_parent_process(pid, exec);
	}
	free(path);
	return (exec->last_exit_status);
}

// Exécute un pipeline de commandes connectées par des pipes
// Parcourt chaque commande, crée les pipes nécessaires, fork les processus
// et attend tous les enfants pour retourner le statut de la dernière commande
int	execute_pipeline(t_command *cmd, t_exec *exec)
{
	int			i;
	char		*path;
	t_command	*cmd_head;

	cmd_head = cmd;
	init_pipe_var(&i, &path);
	while (cmd)
	{
		setup_pipe_if_needed(cmd, exec);
		fork_command(exec, &i);
		if (exec->pidarray[i] == 0)
		{
			set_child_in_redir(cmd, exec, cmd_head);
			set_child_out_pipe(cmd, exec, cmd_head);
			if (is_builtin(cmd->args[0]) != NOT_BUILTIN)
				exec_pipe_bltin(cmd, exec, cmd_head);
			else
				execute_pipe_ext(cmd, exec, cmd_head);
		}
		else
			handle_parent_pipes(cmd, exec);
		cmd = cmd->next;
	}
	wait_all_children(exec, i);
	return (exec->last_exit_status);
}

// Attend un processus enfant avec gestion des signaux
void	wait_single_child(t_exec *exec, int j, int *wstatus)
{
	while (waitpid(exec->pidarray[j], wstatus, 0) == -1)
	{
		if (errno == EINTR)
		{
			if (g_signal == SIGINT)
			{
				kill(exec->pidarray[j], SIGINT);
				g_signal = 0;
			}
			continue ;
		}
		else
		{
			perror("waitpid");
			break ;
		}
	}
}

//takes cmd->args[0] as param
//returns 1 if you should fork, 0 if not
int	do_fork(char *arg)
{
	if (is_builtin(arg) == NOT_BUILTIN || !is_parent_builtin(arg))
		return (1);
	return (0);
}
