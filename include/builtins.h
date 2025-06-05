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
} t_builtin_type;

//builtins

int		bltin_pwd(t_command *cmd); //pwd

int		bltin_echo(t_command *cmd); //echo
int		is_n(char *str);

int		bltin_exit(char **cmd); //exit
int		ft_is_number(char *str);
int		check_long(char *str);

int		bltin_cd(t_command *cmd); //cd
int		cd_errors(t_command *cmd);

int		bltin_env(t_command *cmd, char **env); //env
void	print_strs(char **strs);

int		bltin_export(t_command *cmd, char ***env); //export
int		get_new_env(char ***env, char *cmd);
char	**copy_and_add(char **env, char *cmd);
int		count_strings(char **strs);
char	**copy_env(char **env); //delete later

//utils

int		exec_builtins(t_command *cmd, char ***env);
int		is_builtin(char *cmd);



#endif