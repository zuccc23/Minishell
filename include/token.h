#ifndef TOKEN_H
# define TOKEN_H

typedef enum token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	int						expandable;
	struct s_token			*next;
}	t_token;

#endif