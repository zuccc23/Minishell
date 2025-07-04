/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:29:45 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:29:47 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// returns enum if its a builtin (=ECHO(1), =PWD(2),...)
// returns NOT_BUILTIN(7) if regular command
// takes 'command->args[0]' as parameter
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (NOT_BUILTIN);
	if (ft_strnstr(cmd, "cd", 2) != 0 && ft_strlen(cmd) == 2)
		return (CD);
	else if (ft_strnstr(cmd, "echo", 4) != 0 && ft_strlen(cmd) == 4)
		return (ECHO);
	else if (ft_strnstr(cmd, "pwd", 3) != 0 && ft_strlen(cmd) == 3)
		return (PWD);
	else if (ft_strnstr(cmd, "export", 6) != 0 && ft_strlen(cmd) == 6)
		return (EXPORT);
	else if (ft_strnstr(cmd, "unset", 5) != 0 && ft_strlen(cmd) == 5)
		return (UNSET);
	else if (ft_strnstr(cmd, "env", 3) != 0 && ft_strlen(cmd) == 3)
		return (ENV);
	else if (ft_strnstr(cmd, "exit", 4) != 0 && ft_strlen(cmd) == 4)
		return (EXIT);
	else
		return (NOT_BUILTIN);
}

//execute the right function depending on the builtin called
int	exec_builtins(t_command *cmd, char ***env, int ex_status)
{
	int	exit_status;

	exit_status = 0;
	if (is_builtin(cmd->args[0]) == PWD)
		exit_status = bltin_pwd(cmd);
	if (is_builtin(cmd->args[0]) == ECHO)
		exit_status = bltin_echo(cmd);
	if (is_builtin(cmd->args[0]) == CD)
		exit_status = bltin_cd(cmd, &(*env));
	if (is_builtin(cmd->args[0]) == ENV)
		exit_status = bltin_env(cmd, *env);
	if (is_builtin(cmd->args[0]) == EXPORT)
		exit_status = bltin_export(cmd->args, &(*env));
	if (is_builtin(cmd->args[0]) == UNSET)
		exit_status = bltin_unset(cmd, &(*env));
	if (is_builtin(cmd->args[0]) == EXIT)
		exit_status = return_exit_s(cmd->args, ex_status);
	return (exit_status);
}

//checks for invalid options
int	invalid_option(char **args, char *cmd)
{
	if (args[1] && args[1][0] == '-' && args[1][1])
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": -", STDERR_FILENO);
		ft_putchar_fd(args[1][1], STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		return (2);
	}
	return (ER_OK);
}
