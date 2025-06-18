#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

typedef struct sigaction	t_sa;
extern volatile sig_atomic_t	g_signal;

typedef enum e_shell_mode {
    MODE_INTERACTIVE,// En attente d'une commande
    MODE_EXECUTING,// Exécution d'une commande
    MODE_HEREDOC// Lecture d'un heredoc
} t_shell_mode;
 
//init interface utilisateur

void	handle_sigint(int sig);
void	exec_handle_sigint(int sig);
void	handle_child_signal(void);
void	handle_interactive_signal(void);
void	handle_exec_signal(void);
void	handle_sigquit(int sig);

#endif
