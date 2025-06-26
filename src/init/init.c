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

//reads input with readline
// returns 1 when ctrl + D has been received
// or 0 if not
int	read_input(t_data *shell)
{
	(*shell).input = readline("minishell-1.0$ ");
	if (!(*shell).input)
	{
		write (1, "exit\n", 5);
		free_exec((*shell).exec);
		(*shell).exec = NULL;
		return (1);
	}
	return (0);
}

//add history
//get the tokens from the input
//free the input
void	token_part(t_data *shell)
{
	add_history((*shell).input);
	(*shell).command = NULL;
	(*shell).token = tokenize((*shell).input);
	free((*shell).input);
}

//checks if exit has been called, and exits
void	check_for_exit(t_data *shell)
{
	ft_free_list((*shell).token);
	//EXIT BUILTIN
	if ((*shell).command->args && !(*shell).command->next)
	{
		if ((*shell).command->args[0])
		{
			if (is_builtin((*shell).command->args[0]) == EXIT)
			{
				(*shell).exit_status = bltin_exit((*shell).command->args,\
				(*shell).exit_status);
				free_commands((*shell).command);
				free_exec((*shell).exec);
				exit((*shell).exit_status);
			}
		}
	}
}

//main loop of the program
void	minishell_loop(t_data *shell)
{
	while (1)
	{
		if (g_signal == SIGINT)
			(*shell).exit_status = 130;
		g_signal = 0;
		if (read_input(shell) == 1)
			break;
		if ((*shell).input)
		{
			token_part(shell);
			if ((*shell).token)
			{
				(*shell).parser_status = init_parser(shell);
				if ((*shell).parser_status == 0)
				{
					check_for_exit(shell);
					(*shell).exit_status = execute((*shell));
					free_commands((*shell).command);
					handle_interactive_signal();
				}
				else
					(*shell).exit_status = (*shell).parser_status;
			}
		}
	}
}
