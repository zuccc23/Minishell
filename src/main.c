#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data		shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	minishell_loop(&shell);
	rl_clear_history();
	if (shell.exec)
		free_exec(shell.exec);
	return (0);
}
