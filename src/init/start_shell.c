#include "../../include/minishell.h"

//main loop of the program
void	minishell_loop(t_data *shell)
{
	while (1)
	{
		if (read_input(shell) == 1)
			break ;
		if (shell->input)
		{
			token_part(shell);
			if (shell->token)
			{
				shell->parser_status = init_parser(shell);
				ft_free_list(shell->token);
				if (shell->parser_status == 0)
				{
					check_for_exit(shell);
					shell->exit_status = execute(*shell);
					free_commands(shell->command);
					handle_interactive_signal();
				}
				else
					shell->exit_status = shell->parser_status;
			}
		}
	}
}

//reads input with readline
// returns 1 when ctrl + D has been received
// or 0 if not
int	read_input(t_data *shell)
{
	shell->input = readline("minishell-1.0$ ");
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	if (!shell->input)
	{
		write (1, "exit\n", 5);
		free_exec(shell->exec);
		shell->exec = NULL;
		return (1);
	}
	return (0);
}

//add history
//get the tokens from the input
//free the input
void	token_part(t_data *shell)
{
	add_history(shell->input);
	shell->command = NULL;
	shell->token = tokenize(shell->input);
	free(shell->input);
}

//checks if exit has been called, and exits
void	check_for_exit(t_data *shell)
{
	if (shell->command->args && !shell->command->next)
	{
		if (shell->command->args[0])
		{
			if (is_builtin(shell->command->args[0]) == EXIT)
			{
				shell->exit_status = bltin_exit(shell->command->args, \
				shell->exit_status);
				free_commands(shell->command);
				free_exec(shell->exec);
				exit(shell->exit_status);
			}
		}
	}
}
