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
	handle_interactive_signal();
	while (1)
	{
		input = readline("minishell-1.0# ");
		if (!input)
		{
			write (1, "exit\n", 5);
			break;
		}
		if (*input)
		{
			add_history(input);

			//PARSING
			t_token *head = NULL;
			command = NULL;
			head = tokenize(input);
			if (!head)
			{
				free(input);
				return (1);
			}
			// ft_print_list(head);
			// printf("\n\n\n\n\n");
			// ft_print_list(head);

			int parser_result = init_parser(&env, &head, &command, exit_status);
			if (parser_result != 0)
			{
				if (head)
					ft_free_list(head);
				if (command)
					free_commands(command);
				if (parser_result == 130)
				{
					exit_status = 130;
					continue;
				}
				free(input);
				free_env(env);
				exit(1);
			}
			//EXECUTION
			exit_status = execute(command, env, head);
			//restore interactive signals?
			handle_interactive_signal();
			if (head)
			{
			    printf("Freeing tokens...\n");
    			ft_free_list(head);
  				printf("Tokens freed\n");
			}
			if (command)
				free_commands(command);
		}
		free(input);
	}
	free_env(env);
	return (0);
}
