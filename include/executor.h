#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>

typedef struct s_exex
{
	int		pipe_fd[2]; // fd[0] = lecture, fd[1] = ecriture
	int		count_cmd; // Savoir combien tu as de commande pour gerer la derniere differement
	int		input_fd;   // Ce que la commande lira (STDIN ou pipe precedent)
	int		output_fd;  // Ce que la commande ecrira (STDOUT ou pipe suivant)
	int		infile_fd;
	int		outfile_fd;
	char	**envp;
	int		last_exit_status; // Code d'exit
	pid_t	*pidarray;  // Tableau de tous les pids (si plusieurs commandes)
}	t_exec;

int			execute(t_command *command, t_env *env);
int			execute_single_command(t_command *cmd, t_exec *exec);
int			apply_redirection(t_command *cmd, t_exec *exec);

// UTILS

int 		init_exec(t_env *env, t_exec *exec, t_command *cmd);
char		**lst_to_char_star(t_env *env);
void		free_exec(t_exec *exec);
int			count_commands(t_command *cmd);

#endif
