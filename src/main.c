#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env = NULL;
	t_command	*command = NULL;
	int			exit_status = 0;
	(void)ac;
	(void)av;
	(void)envp;

	// Initialisation du shell + a proteger
	init_env(&env, envp);
	// char **copy_envp = copy_env(envp);
	handle_interactive_signal();
	while (1)
	{
		input = readline("minishell-1.0# ");
		if (!input)
		{
			write (1, "exit\n", 5);
			free_env(env);
			break;
		}
		if (*input)
		{
			add_history(input);
			
			//PARSING
			t_token *head = NULL;
			head = tokenize(input);
			if (!head)
			{
				free(input);
				return (1);
			}
			// ft_print_list(head);
			// printf("\n\n\n\n\n");
			// ft_print_list(head);

			if (init_parser(&env, &head, &command, exit_status) != 0)
				exit(1);
			
			//EXECUTION
			exit_status = execute(command, env);
			//parent signal?

			//BUILTINS
			// if (command->args)
			// {
			// 	if (is_builtin(command->args[0]) >= 0 && is_builtin(command->args[0]) <= 5)

			// 		exit_status = exec_builtins(command, &copy_env);
			// 	if (is_builtin(command->args[0]) == EXIT)
			// 	{
			// 		int	ex_code = bltin_exit(command->args, exit_status);
			// 		ft_free_list(head);
			// 		free_commands(command);
			// 		free(input);
			// 		free_env(env);
			// 		exit(ex_code);
			// 	}
			// }
			ft_free_list(head);
			free_commands(command);
		}
		free(input);
	}
	return (0);
}
