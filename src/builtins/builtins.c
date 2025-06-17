#include "../../include/minishell.h"

bool	is_parent_builtin(const char *cmd_name)
{
	if (cmd_name)
		return (false);
	if (ft_strnstr(cmd, "cd", 2) != 0 && ft_strlen(cmd) == 2)
		return (true);
	else if (ft_strnstr(cmd, "exit", 4) != 0 && ft_strlen(cmd) == 4)
		return (true);
	else if (ft_strnstr(cmd, "export", 6) != 0 && ft_strlen(cmd) == 6)
		return (true);
	else if (ft_strnstr(cmd, "unset", 5) != 0 && ft_strlen(cmd) == 5)
		return (true);
	else
		return (false);
}
