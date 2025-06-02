#include "../../include/minishell.h"

// exit: exit [n]
//     Exit the shell.  
//     Exits the shell with a status of n.  If n is omitted, the exit status
//     is that of the last command executed.
void	bltin_exit(int status)
{
	exit(status);
}
