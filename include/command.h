#ifndef COMMAND_H
# define COMMAND_H

# include "redirection.h"

typedef struct s_command
{
	char					**args;
	t_redirection			*redirections;
	struct s_command		*next;
}	t_command;

#endif
