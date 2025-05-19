#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>

int	execute_single_command(t_command *command, t_env *env);


// UTILS

char	**lst_to_char_star(t_env *env);

#endif
