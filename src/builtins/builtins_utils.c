#include "../../include/minishell.h"

// returns 1 if its a builtin, 0 if regular command
// takes 'command->args[0]' as parameter
int	is_builtin(char *cmd)
{
	if (ft_strnstr(cmd, "cd", 2) != 0 && ft_strlen(cmd) == 2)
		return (1);
	else if (ft_strnstr(cmd, "echo", 4) != 0 && ft_strlen(cmd) == 4)
		return (1);
	else if (ft_strnstr(cmd, "pwd", 3) != 0 && ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strnstr(cmd, "export", 6) != 0 && ft_strlen(cmd) == 6)
		return (1);
	else if (ft_strnstr(cmd, "unset", 5) != 0 && ft_strlen(cmd) == 5)
		return (1);
	else if (ft_strnstr(cmd, "env", 3) != 0 && ft_strlen(cmd) == 3)
		return (1);
	else if (ft_strnstr(cmd, "exit", 4) != 0 && ft_strlen(cmd) == 4)
		return (1);
	else
		return (0);
}
