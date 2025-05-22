#include "../../include/minishell.h"

// get the path (=/usr/bin/ls)
char	*get_path(t_command *command, char **env)
{
	char	*path_line;
	char	**paths;
	char	**joined_paths;
	char	*final_path;
	char	*cmd_tmp;

	if (!command->args || !command->args[0])
		return (NULL);
	init_paths(&paths, &joined_paths, &final_path, &cmd_tmp);
	if (find_path_line(&path_line, env) == 1)
		return (NULL);
	paths = ft_split(path_line + 5, ':');
	if (!paths)
		return (NULL);
	cmd_tmp = ft_strjoin("/", command->args[0]);
	if (!cmd_tmp)
		return (free_paths(&paths, &joined_paths, &cmd_tmp));
	join_paths(paths, cmd_tmp, &joined_paths);
	if (!joined_paths)
		return (free_paths(&paths, &joined_paths, &cmd_tmp));
	final_path = ft_strdup(get_okpath(joined_paths));
	if (!final_path)
		return (free_paths(&paths, &joined_paths, &cmd_tmp));
	free_paths(&paths, &joined_paths, &cmd_tmp);
	return (final_path);
}

//find the right path with access
char	*get_okpath(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] && access(paths[i], F_OK) != 0)
		i++;
	return (paths[i]);
}

//find 'PATH=usr/bin....'
int	find_path_line(char **path_line, char **env)
{
	int	i;

	i = 0;
	if (env[0] == NULL)
		return (1);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
		{
			*path_line = ft_strnstr(env[i], "PATH=", 5);
			return (0);
		}
		i++;
	}
	return (0);
}

// join the possible paths with the command (=/usr/bin + /ls)
int	join_paths(char **paths, char *command, char ***j_path)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	*j_path = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (paths[i])
	{
		(*j_path)[i] = ft_strjoin(paths[i], command);
		if (!(*j_path)[i])
		{
			while (i > 0)
				free((*j_path)[--i]);
			free((*j_path));
			return (1);
		}
		i++;
	}
	(*j_path)[i] = NULL;
	return (0);
}

//init all path variables to NULL
void	init_paths(char ***paths, char ***j_paths, char **f_path, char **cmd_tmp)
{
	*paths = NULL;
	*j_paths = NULL;
	*cmd_tmp = NULL;
	*f_path = NULL;
}


