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
		return (1);
	exec->envp = env;

	// Init signaux
	handle_interactive_signal();

	while (1)
	{
		input = readline("minishell-1.0$ ");
		if (!input)
		{
			write (1, "exit\n", 5);
			free_strs(exec->envp);
			break;
		}
		if (*input)
		{
			add_history(input);
			
			//PARSING
			t_token *head = NULL;
			head = tokenize(input);
			free(input);
			if (head)
			{
				if (init_parser(env, &head, &command, exit_status) == 0)
				{
					ft_free_list(head);
					//EXIT BUILTIN
					if (command->args && !command->next)
					{
						if (is_builtin(command->args[0]) == EXIT)
						{
							exit_status = bltin_exit(command->args, exit_status);
							free_commands(command);
							free_strs(exec->envp);
							exit(exit_status);
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
	return (0);
}
