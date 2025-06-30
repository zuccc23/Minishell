/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:32:18 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:32:19 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// takes command->args as parameter
// returns the the exit status you need to exit the program with
// !! if it returns 1, dont actually exit the program
// exit: exit [n]
//     Exit the shell.  
//     Exits the shell with a status of n.  If n is omitted, the exit status
//     is that of the last command executed.
int	bltin_exit(char **cmd, int exit_status)
{
	if (!cmd[1])
	{
		ft_printf("exit\n");
		return (exit_status);
	}
	if (ft_is_number(cmd[1]) == 0)
	{
		putstr_err("minishell: exit: ", cmd[1], ": numeric argument required\n");
		return (2);
	}
	if (check_long(cmd[1]) == 1)
	{
		putstr_err("minishell: exit: ", cmd[1], ": numeric argument required\n");
		return (2);
	}
	if (cmd[2])
	{
		ft_printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	ft_printf("exit\n");
	return (ft_atoll(cmd[1]) % 256);
}

//same as bltin_exit, but doesnt print "exit",
//just returns the exit code
//or error message if necessary
int	return_exit_s(char **cmd, int exit_status)
{
	if (!cmd[1])
		return (exit_status);
	if (ft_is_number(cmd[1]) == 0)
	{
		putstr_err("minishell: exit: ", cmd[1], ": numeric argument required\n");
		return (2);
	}
	if (check_long(cmd[1]) == 1)
	{
		putstr_err("minishell: exit: ", cmd[1], ": numeric argument required\n");
		return (2);
	}
	if (cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
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
		if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+')
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
