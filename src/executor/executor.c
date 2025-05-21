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

// Gere le cas ou nous avons une seule commande
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
		free(path);
		free_exec(exec);
		exit(127);
	}
	else
		waitpid(pid, NULL, 0);
	free(path);
	free_exec(exec);
	return (0);
}

// Compter le nombre de commande
int	count_commands(t_command *cmd)
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

static int	execute_pipeline(t_command *cmd, t_exec *exec)
{
	int	i;
	int	j;

	i = -1;
	while (cmd)
	{
		char *path = ft_strjoin("/bin/", cmd->args[0]);
		if (cmd->next)
		{
			if (pipe(exec->pipe_fd) == -1)
			{
				perror("pipe");
				free_exec(exec);
				return (-1);
			}
		}
		exec->pidarray[++i] = fork();
		if (exec->pidarray[i] < 0)
		{
			// Verifier sil faut ajouter des free ou protecions
			perror("fork");
			free_exec(exec);
			return (-1);
		}
		else if (exec->pidarray[i] == 0)
		{
			// Child
			if (i > 0)
				dup2(exec->input_fd, STDIN_FILENO);
			if (cmd->next)
			{
				dup2(exec->pipe_fd[1], STDOUT_FILENO);
				close(exec->pipe_fd[0]);
				close(exec->pipe_fd[1]);
			}
			execve(path, cmd->args, exec->envp);
			perror("execve failed");
			exit(127);
		}
		else
		{
			// Parent
			if (cmd->next)
			{
				exec->input_fd = exec->pipe_fd[0];
				close(exec->pipe_fd[1]);
			}
		}
		cmd = cmd->next;
	}
	j = 0;
	while (j <= i)
	{
		waitpid(exec->pidarray[j], NULL, 0);
		j++;
	}
	return (0);
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
		return (execute_pipeline(command, &exec));
	free_exec(&exec);
	return (0);
}
