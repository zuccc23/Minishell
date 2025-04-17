#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_lexer t_lexer;

typedef enum token_type
{
	TOKEN_WORD,
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

t_token			*tokenize(char *input);

// UTILS

t_token_type	get_operator_type(t_lexer *lexer);
int				is_word_expandable(char *str);
int				extract_word_length(t_lexer *lexer);

#endif
