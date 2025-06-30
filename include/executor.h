#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>

typedef struct s_data	t_data;

typedef struct s_exex
{
	int		pipe_fd[2];
	int		count_cmd;
	int		input_fd;
	int		output_fd;
	int		infile_fd;
	int		outfile_fd;
	char	**envp;
	int		last_exit_status;
	pid_t	*pidarray;
}	t_exec;

int			execute(t_data shell);
int			execute_single_command(t_command *cmd, t_exec *exec);
int			execute_pipeline(t_command *cmd, t_exec *exec);
int			do_fork(char *arg);

// UTILS

int			init_exec(t_exec *exec, t_command *cmd);
void		free_exec(t_exec *exec);
int			count_commands(t_command *cmd);
int			validate_command(t_command *cmd, t_exec *exec);
void		init_cmd_var(int *pid, char **path, int *wstatus, int *exit_status);

// SINGLE CMD UTIL

int			handle_fork(int *pid, t_exec *exec, char *path);
int			setup_child_redirections(t_command *cmd, t_exec *exec, char *path);
void		execute_child_builtin(t_command *cmd, t_exec *exec, char *path);
void		execute_child_external(t_command *cmd, char *path, t_exec *exec);
void		handle_child_process(t_command *cmd, t_exec *exec, char *path);
int			prepare_cmd_execution(t_command *cmd, t_exec *exec, char **path);
int			wait_for_child(int pid, int *wstatus);
int			get_exit_status_from_wstatus(int wstatus);
void		cleanup_parent_fds(t_exec *exec);
int			handle_parent_process(int pid, t_exec *exec);

// EXEC PIPE UTILS

void		setup_pipe_if_needed(t_command *cmd, t_exec *exec);
void		fork_command(t_exec *exec, int *i);
void		setup_child_input_redirections(t_command *cmd, t_exec *exec, t_command *cmd_head);
void		setup_child_output_pipes(t_command *cmd, t_exec *exec);
void		exec_pipe_bltin(t_command *cmd, t_exec *exec, t_command *cmd_head);
char		*resolve_cmd_path(t_command *cmd, t_exec *exec);
void		clean_exit_error(t_command *cmd, t_exec *exec, t_command *cmd_head);
void		ex_ext(t_command *cmd, char *path, t_exec *exec, t_command *cmd_hd);
void		execute_pipe_ext(t_command *cmd, t_exec *exec, t_command *cmd_head);
void		init_pipe_var(int *i, char **path);
void		clean_parent_fds(t_exec *exec);
void		setup_next_pipe(t_command *cmd, t_exec *exec);
void		handle_parent_pipes(t_command *cmd, t_exec *exec);
void		update_exit_status_if_last(t_exec *exec, int j, int i, int wstatus);
void		wait_all_children(t_exec *exec, int i);
void		wait_single_child(t_exec *exec, int j, int *wstatus);

#endif
