#ifndef COMMAND_H
# define COMMAND_H

# include "redirection.h"

typedef struct s_command
{
	char					**args;	//Tableau d'arguments. args[0] c'est le nom de la commande
	t_redirection			*redirections; // Liste chainee des redirections associees a la commande
	struct s_command		*next;
}	t_command;

#endif
