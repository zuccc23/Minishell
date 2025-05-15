#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	(void)ac;
	(void)av;
	(void)envp;

	// Initialisation du shell
	//setup_env(envp); --> pour avoir lenvironnement
	handle_signal();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			write (1, "exit\n", 5);
			break;
		}
		// si l'input n'est pas vide on le traite
		if (*input)
		{
			add_history(input);
			printf("\n%s\n", input);
			t_token *head = NULL;
			head = tokenize(input);
			if (!head)
			{
				free(input);
				return (1);
			}
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			ft_print_list(head);
			ft_free_list(head);
		}
		free(input);
	}
	return (0);
}
