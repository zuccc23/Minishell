#include "../../include/minishell.h"

//The env command is used to run a command in a modified environment
// or just to show the current environment variables
// we just need to show the current environment variables?
int	bltin_env(t_command *cmd, char **env)
{
	if (!env)
		return (0);
	if (!cmd->args[1])
		print_strs(env);
	if (invalid_option(cmd->args, "env") == 2)
		return (125);
	if (cmd->args[1])
	{
		ft_printf("minishell: env: too many arguments\n");
		return (1);
	}
	return (ER_OK);
}

//prints char **
void	print_strs(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] != NULL)
	{
		while (strs[i][j])
		{
			write (1, &strs[i][j], 1);
			j++;
		}
		write (1, "\n", 1);
		i++;
		j = 0;
	}
}
