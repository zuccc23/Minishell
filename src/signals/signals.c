#include "../../include/minishell.h"

void    handle_sigint(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    rl_on_new_line();
    write (1, "\n", 1);
    rl_redisplay();
}