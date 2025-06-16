#include "../../include/minishell.h"

// pwd: prints current directory
// returns 1 if failure, 0 if success
int	bltin_pwd(t_command *cmd)
{
	char	buff[1024];
	char	*str;

	if (invalid_option(cmd->args, "pwd") == 2)
		return (2);
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
