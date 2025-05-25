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
