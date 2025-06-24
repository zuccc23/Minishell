#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

typedef struct sigaction		t_sa;
extern volatile sig_atomic_t	g_signal;

//init interface utilisateur

void	handle_sigint(int sig);
void	exec_handle_sigint(int sig);
void	handle_sigquit(int sig);

//sig handlers

void	handle_child_signal(void);
void	handle_interactive_signal(void);
void	handle_exec_signal(void);

#endif
