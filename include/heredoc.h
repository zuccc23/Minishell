#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_exex		t_exec;

typedef struct s_expand_data
{
	char	*exit_str;
	char	**envp;
	char	*result;
	size_t	result_pos;
}	t_expand_data;

int			collect_all_heredocs(t_data shell);
void		heredoc_handle_signal(int sig);
void		close_all_heredoc_fds(t_command *cmd);
int			handle_heredoc(t_data shell, char *delimiter, int *heredoc_fd);
char		*expand_variables(const char *line, t_data shell);
void		write_heredoc_line(int fd, char *line, char *expanded);
int			is_heredoc_interrupted(int status, int fd);

// UTILS

size_t		expanded_len(const char *line, char **env, int error_code);
void		unknown_dollar_len(size_t *len, int *i);
void		exit_code_len(int *i, size_t *len, const char *exit_str);
int			get_var_name_len(const char *str, int start);
void		hdle_env_var_len(const char *line, int *i, size_t *len, char **env);
size_t		find_expd_len(const char *line, char **env, const char *exit_str);
char		*get_env_value(const char *var_name, char **env);
void		handle_env_var(const char *line, size_t *i, t_expand_data *data);
void		handle_var_exp(const char *line, size_t *i, t_expand_data *data);
void		handle_char(const char *line, size_t *i, t_expand_data *data);
void		copy_to_result(t_expand_data *data, const char *str);
void		handle_exit_code(const char *line, size_t *i, t_expand_data *data);
void		free_expand_data(t_expand_data *data);

#endif
