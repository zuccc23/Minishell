#include "../../include/minishell.h"

// returns enum if its a builtin (=ECHO(1), =PWD(2),...)
// returns NOT_BUILTIN(7) if regular command
// takes 'command->args[0]' as parameter
int	is_builtin(char *cmd)
{
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
int	exec_builtins(t_command *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (is_builtin(cmd->args[0]) == PWD)
		exit_status = bltin_pwd();
	if (is_builtin(cmd->args[0]) == ECHO)
		exit_status = bltin_echo(cmd);
	// if (is_builtin(cmd->args[0]) == EXIT)
	// 	exit_status = bltin_echo(cmd);
	return (exit_status);
}
