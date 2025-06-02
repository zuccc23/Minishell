#include "../../include/minishell.h"

int	bltin_echo(t_command *command)
{
	int	i;

	i = 1;
	while (command->args[i])
	{
		ft_printf("%s", command->args[i]);
		if (command->args[i + 1])
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	return (ER_OK);
}
