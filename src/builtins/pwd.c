#include "../../include/minishell.h"

// pwd: returns 1 if failure, 0 if success
int	bltin_pwd(void)
{
	char	buff[1024];
	char	*str;

	str = NULL;
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
