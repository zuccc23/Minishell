/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:39:34 by dahmane           #+#    #+#             */
/*   Updated: 2025/06/30 18:39:35 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_lexer	t_lexer;

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
int				init_lexer_preprocess(t_lexer **lexer, \
char **p_input, char *input);
void			*free_tok_error(t_lexer **lex, t_token **h, char **value, \
char **p_inpu);
t_token			*create_operator_token(t_token_type type);
t_token			*create_word_token(t_token_type type, t_word *word);

#endif
