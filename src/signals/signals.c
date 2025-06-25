#include "../../include/minishell.h"

//variable globale pour recupérer le signal
volatile sig_atomic_t	g_signal;

//gere SIGINT en mode interactif
void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write (1, "\n", 1);
	rl_redisplay();
}

//gere SIGINT en mode exec
void	exec_handle_sigint(int sig)
{
	g_signal = sig;
	if (!isatty(0))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
	}
}

void	handle_sigquit(int sig)
{
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
}
