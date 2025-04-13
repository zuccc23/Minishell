#ifndef UTILS_H
# define UTILS_H


// LIST UTILS

void	add_token_to_list(t_token **token, t_list *new);
t_token	*ft_token_last(t_token *token);
t_token	*create_token(t_token_type type, char *value, int expandable);
char	*extract_operator_value(t_lexer *lexer);

#endif
