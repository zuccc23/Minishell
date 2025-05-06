#ifndef REDIRECTION_H
# define REDIRECTION_H

typedef struct s_token	t_token;
typedef struct s_command	t_command;

typedef enum redir_type
{
	REDIR_INPUT,   // <
	REDIR_OUTPUT,  // >
	REDIR_APPEND,  // >>
	REDIR_HEREDOC  // <<
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type; // Type de redirection, input, output etc
	char					*file;// Nom du fichier ou delimiteur (pour heredoc) 
	struct s_redirection	*next;
}	t_redirection;

// redirections
int				assign_redirections(t_token **token, t_command **command);
int				get_redirections(t_token **token, t_redirection **redir);
t_redirection	*lstlast_redir(t_redirection *lst);
int		get_redir_file(t_token *token, t_redirection **redir);

#endif