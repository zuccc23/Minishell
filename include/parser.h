#ifndef PARSER_H
# define PARSER_H

typedef struct s_token	t_token;

int	check_single_operator(t_token *token);
int	check_content_before_pipe(t_token *token);
int	check_content_after_operator(t_token *token);
int	parse_tokens(t_token *token);

#endif