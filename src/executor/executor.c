#include "../../include/minishell.h"

// Passer de la structure a un char** pour execve
char	**lst_to_char_star(t_env *env)
{
	int		size;
	int		i;
	char	**envp;
	t_env	*tmp;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	i = 0;
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	while (i < size)
	{
		envp[i++] = env->value;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int apply_output_redirection(t_redirection *redir, char *filename)
{
	redir->fd = open(filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(filename);
		return (1);
	}
	return (0);
}

int	execute_single_command(t_command *cmd, t_exec *exec)
{
	int	pid;

	char *path = "/bin/";
	path = ft_strjoin(path, cmd->args[0]);
	pid = fork();
	if (pid < 0)
	{
		perror("Failed fork \n");
		return (-1);
	}
	if (pid == 0)
	{
		execve(path, cmd->args, exec->envp);
		perror("execve failed");
		exit(127);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}
//Compter le nombre de commande
static int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

// Initialiser la structure de lexec
int init_exec(t_env *env, t_exec *exec, t_command *cmd)
{
	exec->cout_cmd = count_commands(cmd);
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->input_fd = STDIN_FILENO;
	exec->output_fd = STDOUT_FILENO;
	exec->envp = lst_to_char_star(env);
	if (!exec->envp)
		return (-1);
	exec->pidarray = NULL;
	return (0);
}

int	execute_pipeline(t_command *cmd, t_redirection *redir, t_exec *exec)
{
	while (cmd)
	{
		// Enfant
		if (exec->pidarray == 0)
		{

		}
		// Parent
		else
		{

		}
		cmd = cmd->next;
	}
}

// Fonction principale qui orchestre toute lexec
int	execute(t_command *command, t_env *env)
{
	int		error_code;
	t_exec	exec;

	error_code = 0;
	error_code = init_exec(env, &exec, command);
	if (error_code != ER_OK)
		return (error_code);
	if (command->next == NULL)
		return (execute_single_command(command, &exec));
	else
		return (execute_pipeline(command, env));
	return (0);
}
