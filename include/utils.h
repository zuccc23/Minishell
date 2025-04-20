#ifndef UTILS_H
# define UTILS_H

// clean the commands and redirections (clean.c)
void	free_commands(t_command *commands);
void	free_strs(char **strs);
void	free_redirections(t_redirection *redir);
void	free_tokens(t_token *token);

#endif