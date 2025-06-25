#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_exex		t_exec;

typedef struct s_expand_context
{
	const char	*line;
	t_env		*env;
	int			error_code;
	char		*exit_str;
}	t_expand_context;

int			collect_all_heredocs(t_data shell);
void		heredoc_handle_signal(int sig);
void		close_all_heredoc_fds(t_command *cmd);
int			handle_heredoc(t_data shell, const char *delimiter, int *heredoc_fd);
char 		*expand_variables(const char *line, t_data shell);

#endif
