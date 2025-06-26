#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		shell;
	(void)ac;
	(void)av;

	//checks if the file descriptor is connected to a terminal (like your terminal window or console)
	// or if the file descriptor is not connected to a terminal (like a file, a pipe, or a redirected output)
	if (!isatty(0))
	{
		ft_putstr_fd("minishell: a tty is expected\n", STDERR_FILENO);
		exit(1);
	}

	// Initialisation du shell + a proteger
	init_shell(&shell);

	shell.exec = malloc(sizeof(t_exec));
	if (!shell.exec)
		return (ER_MALLOC);
	ft_memset(shell.exec, 0, sizeof(t_exec));
	shell.exec->envp = copy_env(envp);
	if (!shell.exec->envp)
		return (ER_MALLOC);

	// Init signaux
	handle_interactive_signal();

	while (1)
	{
		shell.input = readline("minishell-1.0$ ");
		if (!shell.input)
		{
			write (1, "exit\n", 5);
			free_exec(shell.exec);
			shell.exec = NULL;
			break;
		}
		if (*shell.input)
		{
			add_history(shell.input);
			//PARSING
			shell.command = NULL;
			shell.token = tokenize(shell.input);
			free(shell.input);
			if (shell.token)
			{
				if (g_signal == SIGINT)
					shell.exit_status = 130;
				g_signal = 0;
				shell.parser_status = init_parser(&shell);
				if (shell.parser_status == 0)
				{
					ft_free_list(shell.token);
					//EXIT BUILTIN
					if (shell.command->args && !shell.command->next)
					{
						if (shell.command->args[0])
						{
							if (is_builtin(shell.command->args[0]) == EXIT)
							{
								shell.exit_status = bltin_exit(shell.command->args, shell.exit_status);
								free_commands(shell.command);
								free_exec(shell.exec);
								exit(shell.exit_status);
							}
						}
					}
					//EXECUTION
					shell.exit_status = execute(shell);
					free_commands(shell.command);

					//restore interactive signals
					handle_interactive_signal();
				}
				else
					shell.exit_status = shell.parser_status;
			}
		}
	}
	rl_clear_history();
	if (shell.exec)
		free_exec(shell.exec);
	return (0);
}

