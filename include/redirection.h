#ifndef REDIRECTION_H
# define REDIRECTION_H

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

#endif