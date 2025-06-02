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

//utils

int	exec_builtins(t_command *cmd);
int	is_builtin(char *cmd);



#endif