#include "../../include/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	// rl_replace_line("", 0);
	rl_on_new_line();
	write (1, "\n", 1);
	rl_redisplay();
}

void	handle_signal(void)
{
	t_sa	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
