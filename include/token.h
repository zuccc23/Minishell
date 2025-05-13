#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_lexer t_lexer;
typedef struct s_word t_word;

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
	t_word					*word;
	t_token_type			type;
	int						expandable;
	struct s_token			*next;
}	t_token;

// FONCTION PRINCIPALE
t_token			*tokenize(char *input);

//FONCTIONS ACCESSOIRES
int				get_cleaned_word_length(char *input);
void			check_single_quotes(char *str, int *i, int *count);
void			check_double_quotes(char *str, int *i, int *count);

// UTILS

t_token_type	get_operator_type(t_lexer *lexer);
int				is_word_expandable(char *str);
int				extract_word_length(t_lexer *lexer);
int				init_lexer_preprocess(t_lexer **lexer, char **processed_input ,char *input);


#endif
