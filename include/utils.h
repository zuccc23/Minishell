#ifndef UTILS_H
# define UTILS_H


// LIST UTILS

void	add_token_to_list(t_token **token, t_token *new);
t_token	*ft_token_last(t_token *token);
t_token	*create_word_token(t_token_type type, t_word *word);
t_token	*create_operator_token(t_token_type type);
void	extract_operator_value(t_lexer *lexer);
void	ft_print_list(t_token *token);
void	ft_free_list(t_token *token);
void	free_word_list(t_word *word);


int		get_cleaned_word_length(char *input);

int		is_ok_word(char c);
int		is_single_quotes(char c);
int		is_expandable(char c, char next_c);
int		is_double_quotes(char c);
int		is_space(char c);

//

#endif
