#ifndef PARSER_H
# define PARSER_H

typedef struct s_token	t_token;

//check parsing errors
int	check_single_operator(t_token *token);
int	check_content_before_pipe(t_token *token);
int	check_content_after_operator(t_token *token);
int	check_content_after_pipe(t_token *token);
int	parse_tokens(t_token *token);

//clean the input (delete later)
char	**clean(char *s);
void    strs_print(char **strs);

//check characters (for cleaning input, delete later)
int	is_space(char c);
int	is_double_quotes(char c);
int	is_expandable(char c, char next_c);
int	is_single_quotes(char c);
int	is_ok_word(char c);

#endif