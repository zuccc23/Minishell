#include "../../include/minishell.h"

//changes current working directory
//returns 1 if any error occurs, 0 if ok
int	bltin_cd(t_command *cmd)
{
	DIR	*dir;

	if (cd_errors(cmd) != ER_OK)
		return (1);
	dir = opendir(cmd->args[1]);
	if (!dir)
	{
		ft_printf("minishell: cd: %s: ", cmd->args[1]);
		perror("");
		return (1);
	}
	if (chdir(cmd->args[1]) == -1)
	{
		ft_printf("minishell: cd: error changing directories\n");
		closedir(dir);
		return (1);
	}
	if (closedir(dir) == -1)
	{
		ft_printf("minishell: cd: error closing directory stream\n");
		return (1);
	}
	return (ER_OK);
}

int	cd_errors(t_command *cmd)
{
	if (!cmd->args[1])
	{
		ft_printf("minishell: cd: an absolute or relative path must be given");
		ft_printf("\n");
		return (1);
	}
	if (cmd->args[2])
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (ER_OK);
}
