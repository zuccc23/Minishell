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
	char **copy_envp = copy_env(envp);
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
			t_token *head = NULL;
			head = tokenize(input);
			if (!head)
			{
				//printf("je suis ici\n");
				free(input);
				return (1);
			}
			// ft_print_list(head);

			// printf("\n\n\n\n\n");
			// ft_print_list(head);
			init_parser(&env, &head, &command, exit_status);
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
			execute(command, env);
			// if (access(command->args[0], F_OK) == 0)
			// 	execve(command->args[0], command->args, envp);

			//BUILTINS
			// if (command->args)
			// {
			// 	if (is_builtin(command->args[0]) >= 0 && is_builtin(command->args[0]) <= 5)
			// 		exit_status = exec_builtins(command, &copy_envp);
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
