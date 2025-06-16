#ifndef REDIRECTION_H
# define REDIRECTION_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_exex		t_exec;

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
	int						fd;
	struct s_redirection	*next;
}	t_redirection;

// recupere les redirections

int				assign_redirections(t_token **token, t_command **command);
int				get_redirections(t_token **token, t_redirection **redir);
int				get_redir_file(t_token *token, t_redirection **redir);
int				join_redir(t_word *word, t_redirection **redir, char *tmp);
t_redirection	*lstlast_redir(t_redirection *lst);
int				has_valid_redirections(t_command *cmd);

void			safe_close(int *fd);

#endif
