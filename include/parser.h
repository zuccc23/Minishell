#ifndef PARSER_H
# define PARSER_H

typedef struct s_token	t_token;

// init parser

int	init_parser(t_env **env, t_token **token, t_command **commands);

//check parsing errors

int		parse_tokens(t_token *token);

//parser utils

int		check_single_operator(t_token *token);
int		check_content_before_pipe(t_token *token);
int		check_content_after_operator(t_token *token);
int		check_content_after_pipe(t_token *token);
void	print_token_value(t_word *word, t_token *token);

#endif