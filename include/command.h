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
int	get_commands(t_token *token, t_command **commands);
int	new_command(t_token *token, t_command **command, int args_count);
int	count_args(t_token *token);
int	alloc_command(t_command **command, int args_count);

// redirections
int				assign_redirections(t_token **token, t_command **command);
t_redirection	*lstlast_redir(t_redirection *lst);
int	get_redirections(t_token **token, t_redirection **redir);

//check token type
int	is_operator(t_token *token);
int	is_pipe(t_token *token);
int	is_word(t_token *token);

#endif
