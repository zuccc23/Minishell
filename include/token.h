#ifndef TOKEN_H
# define TOKEN_H

typedef enum token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_word
{
	char					*value;
	int						expandable;
	struct s_word			*next;
}	t_word;

typedef struct s_token
{
	t_word					*word;
	t_token_type			type;
	int						expandable;
	struct s_token			*next;
}	t_token;

#endif