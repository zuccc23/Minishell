#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	(void)ac;
	(void)av;
	(void)envp;
	// Initialisation du shell

	while (1)
	{
		// Affichage du prompt et recuperation de l'input
		input = readline("minishell> ");
		if (!input) // ctrl + D ou EOF
		{
			write (1, "exit\n", 5);
			break;
		}
		// si l'input n'est pas vide on le traite
		if (*input)
		{

		}
	}
	return (0);
}
