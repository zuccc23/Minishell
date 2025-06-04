#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*env = NULL;
	t_command	*command = NULL;
	(void)ac;
	(void)av;
	(void)envp;
	// int i = 0;

	// Initialisation du shell + a proteger
	init_env(&env, envp);
	handle_interactive_signal();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write (1, "exit\n", 5);
			free_env(env);
			break;
		}
		if (*input)
		{
			add_history(input);
			t_token *head = NULL;
			head = tokenize(input);
			if (!head)
			{
				free(input);
				return (1);
			}
			// printf("\n\n\n\n\n");
			// ft_print_list(head);
			init_parser(&env, &head, &command);
			// while (command)
			// {
			// 	i = 0;
			// 	while (command->args[i])
			// 	{
			// 		printf("%s ", command->args[i]);
			// 		i++;
			// 	}
			// 	printf("\n");
			// 	if (command->redirections)
			// 	{
			// 		printf("type: %d\n", command->redirections->type);
			// 		if (command->redirections->file)
			// 			printf("%s\n", command->redirections->file);
			// 	}
			// 	command = command->next;
			// }
			
			// if (access(command->args[0], F_OK) == 0)
			// 	execve(command->args[0], command->args, envp);
			if (is_builtin(command->args[0]) != NOT_BUILTIN)
				exec_builtins(command);
			if (is_builtin(command->args[0]) == EXIT)
				exit(bltin_exit(command->args));
			char *str = get_path(command, envp);
			if (str)
			{
				// printf("path: %s\n", str);
				// execve(str, command->args, envp);
				free(str);
			}
			ft_free_list(head);
			free_commands(command);
		}
		free(input);
	}
	return (0);
}
