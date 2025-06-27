#include "../../include/minishell.h"

//initialize minishell 
int	init_shell(t_data *shell, char **envp)
{
	if (!isatty(0))
	{
		ft_putstr_fd("minishell: a tty is expected\n", STDERR_FILENO);
		exit(1);
	}
	init_vars(&(*shell));
	(*shell).exec = malloc(sizeof(t_exec));
	if (!(*shell).exec)
		return (ER_MALLOC);
	ft_memset((*shell).exec, 0, sizeof(t_exec));
	(*shell).exec->envp = copy_env(envp);
	if (!(*shell).exec->envp)
		return (ER_MALLOC);
	handle_interactive_signal();
	g_signal = 0;
	return (ER_OK);
}

//init the variables of shell
int	init_vars(t_data *shell)
{
	(*shell).input = NULL;
	(*shell).token = NULL;
	(*shell).command = NULL;
	(*shell).exec = NULL;
	(*shell).exit_status = 0;
	(*shell).parser_status = 0;
	return (ER_OK);
}
