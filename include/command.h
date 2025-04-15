#ifndef COMMAND_H
# define COMMAND_H

# include "redirection.h"

typedef struct s_token	t_token;

typedef struct s_command
{
	char					**args;	//Tableau d'arguments. args[0] c'est le nom de la commande
	t_redirection			*redirections; // Liste chainee des redirections associees a la commande
	struct s_command		*next;
}	t_command;

// get the commands and their redirections
t_command	*get_commands(t_token *token);
t_command	*new_command(t_token *token, int command_count);
int			count_args(t_token *token);
t_redirection	*get_redirections(t_token **token);

//check token type
int	is_operator(t_token *token);
int	is_pipe(t_token *token);
int	is_word(t_token *token);

#endif
