#include "../../include/minishell.h"

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
void	init_paths(char ***path, char ***jpath, char **fpath, char **cmdtmp)
{
	*path = NULL;
	*jpath = NULL;
	*cmdtmp = NULL;
	*fpath = NULL;
}

//free paths variables
char	*free_paths(char ***paths, char ***j_paths, char **cmd_tmp)
{
	if (*paths)
		free_strs(*paths);
	if (*j_paths)
		free_strs(*j_paths);
	if (*cmd_tmp)
		free(*cmd_tmp);
	return (NULL);
}
