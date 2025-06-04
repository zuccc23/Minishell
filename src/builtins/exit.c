#include "../../include/minishell.h"

// takes command->args as parameter
// returns the the exit status you need to exit the program with
// !! if it returns 1, dont actually exit the program
// exit: exit [n]
//     Exit the shell.  
//     Exits the shell with a status of n.  If n is omitted, the exit status
//     is that of the last command executed.
int	bltin_exit(char **cmd)
{
	if (!cmd[1])
	{
		ft_printf("exit\n");
		return (0);
	}
	if (ft_is_number(cmd[1]) == 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (2);
	}
	if (check_long(cmd[1]) == 1)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (2);
	}
	if (cmd[2])
	{
		ft_printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	ft_printf("exit\n");
	return (ft_atoll(cmd[1]) % 256);
}

// check if a string only has numbers
// returns 1 if its a number, and 0 if it has other characters
int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

//check for long max/min
int	check_long(char *str)
{
	long long	nb;
	long long	min;

	min = (-9223372036854775807LL - 1);
	nb = 0;
	if (ft_strlen(str) > 20)
		return (1);
	nb = ft_atoll(str);
	if (nb >= 9223372036854775807 || nb <= min)
		return (1);
	return (0);
}
