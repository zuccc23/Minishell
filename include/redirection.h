#ifndef REDIRECTION_H
# define REDIRECTION_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;

typedef enum redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

// type = Type de redirection, file = Nom du fichier ou delimiteur
typedef struct s_redirection
{
	t_redir_type			type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

// recupere les redirections

int				assign_redirections(t_token **token, t_command **command);
int				get_redirections(t_token **token, t_redirection **redir);
int				get_redir_file(t_token *token, t_redirection **redir);
int				join_redir(t_word *word, t_redirection **redir, char *tmp);
t_redirection	*lstlast_redir(t_redirection *lst);

#endif