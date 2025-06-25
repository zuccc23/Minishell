#include "../../include/minishell.h"

int	init_shell(t_data *minishell)
{
	(*minishell).input = NULL;
	(*minishell).token = NULL;
	(*minishell).command = NULL;
	(*minishell).exec = NULL;
	(*minishell).exit_status = 0;
	return (ER_OK);
}