#include "../../include/minishell.h"

//variable globale pour recupérer le signal
volatile sig_atomic_t	g_signal;

//gere SIGINT en mode interactif
void	handle_sigint(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write (1, "\n", 1);
	rl_redisplay();
}

//gere SIGINT en mode exec
void	exec_handle_sigint(int sig)
{
	g_signal = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
}

//gere les signaux en mode interactif
void	handle_interactive_signal(void)
{
	t_sa	sa;
	// t_sa	sa_quit;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigquit(int sig)
{
	printf("Quit (core dumped)\n");
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	// write(1, "\n", 1);
}

//gere les signaux en mode exec
void	handle_exec_signal(void)
{
	t_sa	sa;

	sa.sa_handler = exec_handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);

	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

//gere les signaux dans le process enfant
void	handle_child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
