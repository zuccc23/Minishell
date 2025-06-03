#include "../../include/minishell.h"

void	safe_close(int *fd)
{
	if (*fd != -1 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO
		&& *fd != STDERR_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
}
