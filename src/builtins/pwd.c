#include "../../include/minishell.h"

// pwd: prints current directory
// returns 1 if failure, 0 if success
int	bltin_pwd(t_command *cmd)
{
	char	buff[1024];
	char	*str;

	str = NULL;
	if (cmd->args[1][0] == '-')
	{
		ft_printf("minishell: pwd: invalid option\n");
		return (2);
	}
	str = getcwd(buff, 1024);
	if (!str)
	{
		perror("pwd: getcwd");
		return (1);
	}
	if (str)
		ft_printf("%s\n", str);
	return (ER_OK);
}
