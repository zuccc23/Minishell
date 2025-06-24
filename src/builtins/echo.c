#include "../../include/minishell.h"

//prints strings
// option -n removes '\n'
// returns only 0 bc it rarely fails
int	bltin_echo(t_command *cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd->args[i] && is_n(cmd->args[i]) == 1)
	{
		i++;
		n = 1;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (ER_OK);
}

//checks for valid option -n
int	is_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] != '-' || !str[i + 1])
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
