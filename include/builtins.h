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

int	bltin_pwd(void);

int	bltin_echo(t_command *command);
int	is_n(char *str);

int	bltin_exit(char **cmd);
int	ft_is_number(char *str);
int	check_long(char *str);

//utils

int	exec_builtins(t_command *cmd);
int	is_builtin(char *cmd);



#endif