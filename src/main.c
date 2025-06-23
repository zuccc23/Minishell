#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input = NULL;
	char		**env = NULL;
	t_command	*command = NULL;
	t_exec		*exec = NULL;
	int			exit_status = 0;
	(void)ac;
	(void)av;

	// Initialisation du shell + a proteger

	env = copy_env(envp);
	if (!env)
		return (1);
	exec = malloc(sizeof(t_exec));
	if (!exec)
	{
		free_strs(env);
		return (1);
	}
	ft_memset(exec, 0, sizeof(t_exec));
	exec->envp = env;

	// Init signaux
	handle_interactive_signal();

	while (1)
	{
		input = readline("minishell-1.0$ ");
		if (!input)
		{
			write (1, "exit\n", 5);
			free_exec(exec);
			exec = NULL;
			break;
		}
		if (*input)
		{
			add_history(input);
			//PARSING
			t_token *head = NULL;
			command = NULL;
			head = tokenize(input);
			free(input);
			if (head)
			{
				// printf("%d\n", g_signal);
				if (g_signal != 0)
					exit_status = g_signal;
				if (init_parser(exec->envp, &head, &command, exit_status) == 0)
				{
					g_signal = 0;
					ft_free_list(head);
					//EXIT BUILTIN
					if (command->args && !command->next)
					{
						if (command->args[0])
						{
							if (is_builtin(command->args[0]) == EXIT)
							{
								exit_status = bltin_exit(command->args, exit_status);
								free_commands(command);
								free_exec(exec);
								exit(exit_status);
							}
						}
					}
					//EXECUTION
					exit_status = execute(command, env, &exec);
					free_commands(command);
					
					//restore interactive signals
					handle_interactive_signal();
				}
			}
		}
	}
	if (exec)
		free_exec(exec);
	return (0);
}

//ctrl C signal <3
//export $USER, echo $USER <3
//Unset USER, echo $USER <3
//Export test= « ls -l » !
