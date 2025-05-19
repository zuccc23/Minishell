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

static void	execute_command(t_command *cmd, char **envp)
{
	int	pid;

	char *path = "/bin/";
	path = ft_strjoin(path, cmd->args[0]);
	pid = fork();
	if (pid < 0)
	{
		perror("Failed fork \n");
		return ;
	}
	if (pid == 0)
	{
		execve(path, cmd->args, envp);
		perror("execve failed");
		exit(127);
	}
	else
		waitpid(pid, NULL, 0);
}

int apply_output_redirection(t_redirection *redir, char *filename)
{
	redir->fd = open(filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(filename);
		return (1);
	}
}

int	execute_single_command(t_command *command, t_env *env)
{
	char	**envp;

	envp = lst_to_char_star(env);
	if (!envp)
		return (-1);
	execute_command(command, envp);
	free(envp);
	return (0);
}
