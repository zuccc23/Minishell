#ifndef BUILTINS_H
# define BUILTINS_H

typedef enum e_builtin_type {
	CD,
	ECHO,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_BUILTIN
}	t_builtin_type;

//builtins

int		bltin_pwd(t_command *cmd); //pwd

int		bltin_cd(t_command *cmd); //cd
int		cd_errors(t_command *cmd);

int		bltin_echo(t_command *cmd); //echo
int		is_n(char *str);

int		bltin_exit(char **cmd, int exit_status); //exit
int		return_exit_s(char **cmd, int exit_status);
int		ft_is_number(char *str);
int		check_long(char *str);

int		bltin_env(t_command *cmd, char **env); //env
void	print_strs(char **strs);

int		bltin_unset(t_command *cmd, char ***env); //unset
int		get_new_env_unset(char ***env, char *cmd);
char	**copy_and_remove(char **env, char *cmd);
int		is_same_var(char *str1, char *str2);
size_t	char_position(char *str, char c);

int		bltin_export(t_command *cmd, char ***env); //export
int		get_new_env(char ***env, char *cmd);
char	**copy_and_add(char **env, char *cmd);
char	**copy_and_replace(char **env, char *cmd);

//export utils

int		count_strings(char **strs);
int		check_args(t_command *cmd);
int		check_export(char *cmd);
int		is_same_var_exp(char *str1, char *str2);

//utils

int		exec_builtins(t_command *cmd, char ***env, int ex_status);
int		is_builtin(char *cmd);
int		invalid_option(char **args, char *cmd);
bool	is_parent_builtin(const char *cmd_name);

#endif
