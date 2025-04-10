#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	struct sigaction sa;
	(void)ac;
	(void)av;
	(void)envp;
	// Configuration de la structure 
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;

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
			add_history(input);
		}
	}
	return (0);
}
